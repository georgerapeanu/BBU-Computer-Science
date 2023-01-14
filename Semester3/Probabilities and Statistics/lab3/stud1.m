# asfasfsafsa

n = input("Please input n: ");

printf("%f\n", tcdf(0, n));
printf("%f\n", tcdf(1, n) - tcdf(-1, n));
alfa = input("Please input alfa: ");
printf("%f\n", tinv(alfa, n));
printf("%f\n", tinv(1 - alfa, n));