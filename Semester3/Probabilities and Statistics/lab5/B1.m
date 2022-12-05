x = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 3 5 12 6 10 7];
n = length(x);
x_bar = mean(x);
sigma = 5;
condfidence_level = input("Enter value of 1-alfa: ");
alfa = 1 - condfidence_level;
z = norminv(1 - alfa / 2);
Z = norminv(alfa / 2);
m1 = x_bar - sigma / sqrt(n) * z;
m2 = x_bar - sigma / sqrt(n) * Z;

printf("Confidence interval with known sigma is %d %d\n", m1, m2);

# b
s = std(x);
t = tinv(1 - alfa/2, n - 1);
T = tinv(alfa/2, n - 1);

m3 = x_bar - s / sqrt(n) * t;
m4 = x_bar - s / sqrt(n) * T;

printf("Confidence interval with unknown sigma is %d %d\n", m3, m4);

# c

s2 = var(x);
_chai1 = chi2inv(1 - alfa / 2, n - 1);
_chai2 = chi2inv(alfa / 2, n - 1);

m5 = (n - 1) * s2 / _chai1;
m6 = (n - 1) * s2 / _chai2;

printf("Confidence interval for variance is %d %d\n", m5, m6);
printf("Confidence interval for the theoretical standard deviation is %d %d\n", sqrt(m5), sqrt(m6));
