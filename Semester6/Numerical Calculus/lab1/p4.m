[x, y] = meshgrid(linspace(-2, 2, 50), linspace(0.5, 4.5, 50));
f = @(x, y) sin(exp(x)) .* cos(log(y));
subplot(2, 1, 1);
mesh(x, y, f(x, y));
subplot(2, 1, 2);
plot3(x, y, f(x, y));