syms x
f = sin(x)
t3 = taylor(f, x, 0, 'order', 3);
t5 = taylor(f, x, 0, 'order', 5);

ezplot(f, [-pi, pi]);
hold on;
ezplot(t3, [-pi, pi]);
hold on;
ezplot(t5, [-pi, pi]);
hold on;
legend();

approx = double(subs(taylor(f, x, 0, 'order', 7), pi/5));
printf("sin(pi/5) is approximately %.10f, error %.10f", approx, approx - double(subs(f, pi/5)));

approx = double(subs(taylor(f, x, 0, 'order', 7), 10 * pi/3));
printf("sin(10 * pi/3) is approximately %.10f, error %.10f", approx, approx - double(subs(f, 10 * pi/3)));