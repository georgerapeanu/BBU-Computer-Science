syms x;
f = exp(x);
t1 = taylor(f, x, 0, 'order', 1);
t2 = taylor(f, x, 0, 'order', 2);
t3 = taylor(f, x, 0, 'order', 3);
t4 = taylor(f, x, 0, 'order', 4);

ezplot(f, [-3, 3]);
hold on;
ezplot(t1, [-3, 3]);
hold on;
ezplot(t2, [-3, 3]);
hold on;
ezplot(t3, [-3, 3]);
hold on;
ezplot(t4, [-3, 3]);
legend();

approx = double(subs(taylor(f, x, 0, 'order', 11), 1));
printf("e is approximately %.10f, error %.10f", approx, approx - double(subs(f, 1)));