# asfasfsafsa

n = input("Please input n: ");

printf("%f\n", chi2cdf(0, n));
printf("%f\n", chi2cdf(1, n) - chi2cdf(-1, n));
alfa = input("Please input alfa: ");
printf("%f\n", chi2inv(alfa, n));
printf("%f\n", chi2inv(1 - alfa, n));