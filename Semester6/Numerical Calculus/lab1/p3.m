R = 3.8;
r = 1;
x = @(t) (R + r) .* cos(t) - r * cos((R./r.+1) .* t);
y = @(t) (R + r) .* sin(t) - r * sin((R./r.+1) .* t);
t_range = linspace(0, 10 * pi, 1000);

%x = subs(x, {R, r}, {3.8, 1});
%y = subs(y, {R, r}, {3.8, 1});
plot(x(t_range), y(t_range));