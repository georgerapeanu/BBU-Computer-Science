syms x
f = log(1 + x)
t2 = taylor(f, x, 0, 'order', 2);
t5 = taylor(f, x, 0, 'order', 5);

ezplot(f, [-0.9, 1]);
hold on;
ezplot(t2, [-0.9, 1]);
hold on;
ezplot(t5, [-0.9, 1]);
hold on;
legend();

approx = double(subs(taylor(f, x, 0, 'order', 70), 1));
printf("ln(2) is approximately %.10f, error %.10f", approx, approx - double(subs(f, 1)));
printf("For 5 decimals, something like 10**5 should be used, not doing that");

f = log(1 - x);
printf("formula for ln(1 - x) would be -x-x^2/2-x^3/3-...");
printf("taylor function of order 5 is\n%s", disp(taylor(f, x, 0, 'order', 5)) );

f = log((1 + x) / (1 - x));
printf("formula for ln((1 + x) / (1 - x)) = ln(1 + x) - ln(1 - x) would be 2x+2x^3/3-...");
printf("taylor function of order 5 is\n%s", disp(taylor(f, x, 0, 'order', 5)) );

# (1+x)/(1-x) = 2
# 1 + x = 2 - 2x
# 3x = 1
# x = 1/3
approx = double(subs(taylor(f, x, 0, 'order', 10), 1/3));
printf("ln(2) is approximately %.10f, error %.10f", approx, approx - log(2))


#printf("sin(10 * pi/3) is approximately %.10f using taylor", double(subs(taylor(f, x, 0, 'order', 7), 10 * pi/3)));