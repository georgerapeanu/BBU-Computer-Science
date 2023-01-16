#3. Nickel powders are used in coating used to shield electronoic equipment.
# A random sample is selected, and the size of nickel particles in each coating
# are recorded(they are assumed to be approximately normally distributed):
# 3.26 1.89 2.42 2.03 3.07 2.95 1.39 3.06 2.46 3.35 1.56 1.79 1.76 3.82 2.42 2.96
# a. Find a 95% confidence interval for the average size of nickel particles.
# b. At the 1% significance level, on average, 
# do these nickel particles seem to be smaller than 3

NICKEL_SIZES = [3.26 1.89 2.42 2.03 3.07 2.95 1.39 3.06 2.46 3.35 1.56 1.79 1.76 3.82 2.42 2.96];

#a.

confidence_level = input("Please enter the confidence level for a confidence interval for the average size of nickel particles: ");

#(1-alpha) confidence interval => alpha = 1 - confidence_level
alpha = 1 - confidence_level;

# "they are assumed to be approximately normally distributed" -> we can use ztest, ttest, etc. and formulas related to such distribution.
# standard deviation and variance are unknown.
# For this reason, we will use the Student T distribution:
# (X_bar - mean) / (s / sqrt(n)) is part of T(n - 1)


X_bar = mean(NICKEL_SIZES);
s = std(NICKEL_SIZES);
n = length(NICKEL_SIZES);

# computing the quantiles for T(n-1) which give a (1-alpha) confidence interval in the distribution
t1 = tinv(alpha / 2, n - 1);
t2 = tinv(1 - alpha / 2, n - 1);

# Let t1 and t2 such that P(t1 <= T <= t2) = 1 - alpha, where T follows T(N - 1)
# (X_bar - mean) / (s / sqrt(n)) is part of T(n - 1)
# t1 <= (X_bar - mean) / (s / sqrt(n)) <= t2
# t1 * (s / sqrt(n)) <= X_bar - mean <= t2 * (s / sqrt(n))
# t1 * (s / sqrt(n)) - X_bar <= -mean <= t2 * (s / sqrt(n)) - X_bar
# X_bar - t2 * (s / sqrt(n)) <= mean <= X_bar - t1 * (s / sqrt(n))
# These are the bounds for the required confidence interval

CONF_L = X_bar - t2 * (s / sqrt(n));
CONF_R = X_bar - t1 * (s / sqrt(n));

printf("A %4.4f confidence interval for the average size of nickel particles is: (%4.4f, %4.4f)\n", confidence_level, CONF_L, CONF_R);

#b.
alpha = input("Please input the significance level: ");

# We still do not know the variance or standard deviation, so we will use a ttest
# The null hypothesis H0 is 
# H0: mean=3
# The alternative hypothesis H1 is:
# H1: mean < 3
# This gives as a left tailed test.
[H, PVAL, CI, STATS] = ttest(NICKEL_SIZES, 3, "tail", "left", "alpha", alpha);

if H == 0
  # This means that the null hypothesis is not rejected
  printf("The null hypothesis is not rejected\n");
  printf("The nickels seem to have, on average, a size of %d\n", 3);
else
  # This means that the null hypothesis is rejected
  printf("The null hypothesis is rejected\n");
  printf("The nickels seem to have, on average, a size smaller than %d\n", 3);
end

printf("The pval of the test is %4.4f\n", PVAL);
printf("A confidence interval for the average size, at %4.4f confidence level is (%4.4f, %4.4f)\n", 1 - alpha, CI(1), CI(2));
printf("The value of the test statistic is %4.4f\n", STATS.tstat);
# Rejection region for the left tailed test is the alpha quantile of the distribution used.
printf("Rejection region for this test is (%4.4f, %4.4f)\n", -inf, tinv(alpha, n - 1));
