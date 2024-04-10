disp("a)")
x_range = linspace(-4, 7.2, 100);
p = @(x) x.^5 -5.*x.^4 -16.*x.^3 + 16.*x.^2 - 17.*x + 21;
plot(x_range, p(x_range))
disp("poly");
p_coefs = [1, -5, -16, 16, -17, 21]
disp("b)")
disp(p(-2.5))
disp("c)")
disp(roots(p_coefs))