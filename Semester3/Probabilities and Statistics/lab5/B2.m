PREMIUM_MILAGE = [22.4 21.7 24.5 23.4 21.6 23.3 22.4 21.6 24.8 20.0];
REGULAR_MILAGE = [17.7 14.8 19.6 19.6 12.1 14.8 15.4 12.6 14.0 12.2];



# a)
PREMIUM_MEAN = mean(PREMIUM_MILAGE);
REGULAR_MEAN = mean(REGULAR_MILAGE);

n1 = length(PREMIUM_MILAGE);
n2 = length(REGULAR_MILAGE);
s12 = var(PREMIUM_MILAGE);
s22 = var(REGULAR_MILAGE);

sp2 = ((n1 - 1) * s12 + (n2 - 1) * s22) / (n1 + n2 - 2);
sp = sqrt(sp2);

confidence_level = input("Please enter the confidence level: ");
alpha = 1 - confidence_level;

t1 = tinv(alpha / 2, n1 + n2 - 2);
t2 = tinv(1 - alpha / 2, n1 + n2 - 2);

CONF_L = (PREMIUM_MEAN - REGULAR_MEAN) - t2 * sp * sqrt(1 / n1 + 1 / n2);
CONF_R = (PREMIUM_MEAN - REGULAR_MEAN) - t1 * sp * sqrt(1 / n1 + 1 / n2);

printf("%4.4f confidence interval for difference of means with unknown equal deviations is %4.4f %4.4f\n", confidence_level, CONF_L, CONF_R);

# b)

c = (s12 / n1) / (s12 / n1 + s22 / n2);
n = 1 / (c^2/(n1 - 1) + (1-c)^2/(n2-1));
t1 = tinv(alpha / 2, n);
t2 = tinv(1 - alpha/2, n);
CONF_L = (PREMIUM_MEAN - REGULAR_MEAN) - t2 * sqrt(s12 / n1 + s22 / n2);
CONF_R = (PREMIUM_MEAN - REGULAR_MEAN) - t1 * sqrt(s12 / n1 + s22 / n2);
printf("%4.4f confidence interval for difference of means with unknown different deviations is %4.4f %4.4f\n", confidence_level, CONF_L, CONF_R);

# c)

f1 = finv(alpha / 2, n1 - 1, n2 - 1);
f2 = finv(1 - alpha / 2, n1 - 1, n2 - 1);
CONF_L = f1 * s22/s12;
CONF_R = f2 * s22/s12;
printf("%4.4f confidence interval for ratio of variances %4.4f %4.4f\n", confidence_level, CONF_L, CONF_R);
