syms x
f = (x + 1) / (3 * x ** 2 + 2 * x + 1);
x_range = linspace(-2, 4, 10);
y_range = eval(subs(f, x, x_range));
p = lagrange(x_range, y_range);
printf("Polynomial is:");
disp(p);

hold on;
nodes = scatter(x_range, y_range);
set(nodes, 'DisplayName', 'Nodes');
hold on;
plot_range=linspace(-2, 4, 200);
f_val = eval(subs(f, x, plot_range));
f_plot=plot(plot_range, f_val);
set(f_plot, 'DisplayName', 'F');
hold on;
lf_val = polyval(p, plot_range);
lf=plot(plot_range, lf_val);
set(lf, 'DisplayName', 'LF');
hold on;
d_f_lf_val = abs(f_val - lf_val);
d_f_lf=plot(plot_range, d_f_lf_val);
printf("Maximum absolute difference is %.4f\n", max(d_f_lf_val));
set(d_f_lf, 'DisplayName', 'F - LF');
legend();
hold off;
printf("Absolute difference at 1/2 is %.4f\n", abs(polyval(p, 1/2) - eval(subs(f, x, 1/2))));