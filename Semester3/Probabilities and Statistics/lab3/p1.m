# asfasfsafsa

u = input("Please input u: ");
o = input("Please input o: ");

printf("%f\n", normcdf(0,u, o));
printf("%f\n", normcdf(1,u, o) - normcdf(-1,u, o));
alfa = input("Please input alfa: ");
printf("%f\n", norminf(alfa, u, 0));
printf("%f\n", norminf(1 - alfa, u, 0));