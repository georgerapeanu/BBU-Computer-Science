PREMIUM_MILAGE = [22.4 21.7 24.5 23.4 21.6 23.3 22.4 21.6 24.8 20.0];
REGULAR_MILAGE = [17.7 14.8 19.6 19.6 12.1 14.8 15.4 12.6 14.0 12.2];

n1 = length(PREMIUM_MILAGE);
n2 = length(REGULAR_MILAGE);
s12 = var(PREMIUM_MILAGE);
s22 = var(REGULAR_MILAGE);

alpha = 0.05;
[h, pval, ci, stats] = vartest2(PREMIUM_MILAGE, REGULAR_MILAGE, "alpha", alpha, "tail", "both");

if h == 0
  printf("The null hypothesis is not rejected\n");
  printf("The variances seem to be equal\n");
else 
  printf("The null hypothesis is rejected\n");
  printf("The variances don't seem to be equal\n");
end
printf("pvalue is %4.4f\n", pval);
printf("observed value is %4.4f\n", stats.fstat);
printf("Confidence interval for the ratio is %4.4f %4.4f\n", ci(1), ci(2))
printf("Rejection region is [%4.4f, %4.4f] U  [%4.4f, %4.4f]\n", 
  -inf,
  finv(alpha / 2, n1 - 1, n2 - 1), 
  finv(1 - alpha/2, n1 - 1, n2 - 1),
  inf);
  
 
n = NaN;
t2 = NaN;
 
if h == 0
  n = n1 + n2 - 2;
else 
  c = (s12 / n1) / (s12 / n1 + s22 / n2);
  n = 1 / (c^2/(n1 - 1) + (1-c)^2 / (n2-1));
end

t2 = tinv(1 - alpha, n);

[h, pval, ci, stats2] = ttest2(PREMIUM_MILAGE, REGULAR_MILAGE, "alpha", alpha, "tail", "right")

if h == 0
  printf("The null hypothesis is not rejected\n");
  printf("The means seem to be equal\n");
else
  printf("The null hypothesis is rejected\n");
  printf("The means seem to be different\n");
end


printf("pvalue is %4.4f\n", pval);
printf("observed value is %4.4f\n", stats2.tstat);
printf("Confidence interval for the difference is %4.4f %4.4f\n", ci(1), ci(2))
printf("Rejection region is [%4.4f, %4.4f]\n", 
  t2,
  inf);
