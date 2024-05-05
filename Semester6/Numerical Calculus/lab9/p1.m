clear all;
x_nodes = linspace(-2, 4, 7);
f = (x_nodes + 1) ./ (3 .* x_nodes .** 2 + 2 .* x_nodes + 1);
fd = ((3 .* x_nodes .** 2 + 2 .* x_nodes + 1) - (x_nodes + 1) .* (6 .* x_nodes + 2)) ./ (3 .* x_nodes .** 2 + 2 .* x_nodes + 1).**2;

x_range = linspace(-2, 4, 300);
f_x_range = (x_range + 1) ./ (3 * x_range .** 2 + 2 * x_range + 1);
s = spline(x_nodes, f, x_range);
syms x;
lagrange = newton(x_nodes, f);
hermite = newton(x_nodes, fd); 

plot(x_range, f_x_range);
hold on;
plot(x_range, eval(subs(lagrange(size(lagrange)(2)), x, x_range)));
hold on;
plot(x_range, eval(subs(hermite(size(hermite)(2)), x, x_range)));
hold on;
plot(x_range, s);