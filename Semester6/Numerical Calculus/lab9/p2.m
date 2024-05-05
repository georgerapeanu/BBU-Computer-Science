clear all;
x_nodes = [-1, -1 / 2, 0, 1 / 2, 1, 3 / 2];
f_nodes = x_nodes .* sin(pi .* x_nodes);

x_range = linspace(-1, 3 / 2, 200);
f_range = x_range .* sin(pi .* x_range);

fs1 = spline(x_nodes, f_nodes, x_range);

fc = [pi, f_nodes, - 1]
fs2 = spline(x_nodes, fc, x_range);

fs3 = pchip(x_nodes, f_nodes, x_range);

plot(x_range, f_range, 'ko', x_range, fs1, 'r--', x_range, fs2, 'g--', x_range, fs3, 'b-.');
legend('f', 'spline', 'complete spline', 'p-wise cubic spline');