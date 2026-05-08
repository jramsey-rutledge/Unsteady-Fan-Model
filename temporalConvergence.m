data = load('error_vs_time.dat');

dt = data(:,1);
err = data(:,2);

loglog(dt, err, 'o-')
grid on
xlabel('dt')
ylabel('Error')
title('Temporal Error Plot')

% compute slope
p = polyfit(log(dt), log(err), 1);
disp(['Order = ', num2str(-p(1))])