f = @(x) sin(x);
g = @(x) sin(2.*x);
h = @(x) sin(3.*x);
x_range = linspace(0, 2 * pi, 100);

subplot(3, 1, 1)
plot(x_range, f(x_range))
subplot(3, 1, 2)
plot(x_range, g(x_range))
subplot(3, 1, 3)
plot(x_range, h(x_range))