clear; clc; close all;

%% --- USER INPUT ---
Nx = 64;          % must match simulation
Ny = 64;
Lx = 1.0;            % change per case
Ly = 1.0;
bx = 2;
by = 2;
A  = 0.1;
dt = 0.5;      % This is your dt * writeInterval
Nt = 40;       % This is Nt / writeInterval


%% --- Create mesh ---
dx = Lx/Nx;
dy = Ly/Ny;

x = 0.5*dx + (0:Nx-1)*dx;
y = 0.5*dy + (0:Ny-1)*dy;

[X,Y] = meshgrid(x,y);

%% --- Create temperature plot --

% streamline function
Psi = -(A/(2*pi)) .* sin(2*pi*X./(bx*Lx)) .* sin(2*pi*Y./(by*Ly));

% --- Animation setup --- %
video = VideoWriter('roomFanAnimation.mp4','MPEG-4');
video.FrameRate = 15;
open(video);

%% --- Figure setup ---
figure

for n = 1:Nt

    %% current time
    t = n * dt;

    %% filename
    filename = sprintf('T_%.6f.dat', t);

    %% check if file exists
    if ~isfile(filename)
        fprintf('Missing file: %s\n', filename);
        continue
    end

    %% load data
    T_full = load(filename);

    Nx2 = Nx + 2;
    Ny2 = Ny + 2;

    %% reshape
    T_full = reshape(T_full,[Nx2,Ny2]);

    %% remove ghost cells
    T = T_full(2:end-1,2:end-1);

    %% average temperature
    Tavg = mean(T(:));

    %% plotting
    clf

    contourf(X,Y,T,50,'LineColor','none')

    hold on

    %contour(X,Y,Psi,10,'k','LineWidth',1)

    %% formatting
    clim([290 300])
    colormap(jet)
    colorbar

    xlabel('x')
    ylabel('y')

    title(sprintf('Temperature Field at t = %.3f s',t))

    subtitle(sprintf('Average Temperature = %.2f K',Tavg))

    axis equal tight

    drawnow
    
    pause(0.02)
    frame = getframe(gcf);
    writeVideo(video,frame);
end

close(video);