data = load('error_vs_grid.dat');

N = data(:,1);
err = data(:,2);

loglog(N, err, 'o-')
grid on
xlabel('N')
ylabel('Error')
title('Spatial Error Plot')

% compute slope
p = polyfit(log(N), log(err), 1);
disp(['Order = ', num2str(-p(1))])

