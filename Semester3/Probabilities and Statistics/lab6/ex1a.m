
%example explaination
% the null hyp is H0: mu=0
% the alt hyp is H1: mu < 9
% left tailed test for the mean, when sigma is known
% also with prints telling what the programming is doing at a given time
alpha = 0.05;
sigma = 5;
x = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 3 5 12 6 10 7];
n = length(x);
miu = 9;
[h,p,_,z,_] = ztest(x, miu, sigma, "alpha", alpha, "tail", "left");
if h == 0
  printf("the null hypothesis h0 is not rejected\n");
  printf("The data suggests that the standard is met\n");
else 
  printf("the null hypothesis h0 is rejected\n");
  printf("The data suggests that the standard is not met\n");
endif

z2=norminv(alpha);
RR = [-inf, z2];
printf("The rejection region is (%.4f %.4f)\n", RR);
printf("The observed value of the test statistic is %.4f\n", z);
printf("The p-value of the test statistic is %.4f\n", p);