# asfasfsafsa

n = input("Please input n: ");
m = input("Please input m: ");

printf("%f\n", fcdf(0, n, m));
printf("%f\n", fcdf(1, n, m) - fcdf(-1, n, m));
alfa = input("Please input alfa: ");
printf("%f\n", finv(alfa, n, m));
printf("%f\n", finv(1 - alfa, n, m));