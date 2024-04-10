# 999 ^ 1/3 = 10 * (999/1000) ^ (1/3)
#= 10 * (1 - 1/1000)^(1/3)

syms x;
approx_f = 1 + (1/3) * x + (1/3 * (1/3 - 1) / 2) * x ^ 2 + (1/3 * (1/3 - 1) * (1 / 3 - 2) / 6) * x ^ 3

approx = 10 * double(subs(approx_f, -1/1000));
printf("999^(1/3) is approximately %.10f, error %.10f", approx, approx - 999^(1/3));

