
%example explaination
% the null hyp is H0: mu=0
% the alt hyp is H1: mu < 9
% left tailed test for the mean, when sigma is known
% also with prints telling what the programming is doing at a given time
alpha = 0.05;
sigma = 5;
x = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 3 5 12 6 10 7];
n = length(x);
miu = 5.5;
[h,p,_,stats] = ttest(x, miu, "alpha", alpha, "tail", "right");
if h == 0
  printf("the null hypothesis h0 is not rejected\n");
  printf("The data suggests that the number of stored files does exceed %.4f\n", miu);
else 
  printf("the null hypothesis h0 is rejected\n");
  printf("The data suggests that the number of stored files does not exceed %.4f\n", miu);
endif

t2=tinv(1 - alpha, length(x) - 1);
RR = [t2, inf];
printf("The rejection region is (%.4f %.4f)\n", RR);
printf("The observed value of the test statistic is %.4f\n", stats.tstat);
printf("The p-value of the test statistic is %.4f\n", p); 

% variance(s2) can be tested with vartest
%  2 populations -> s2.1/s2.2 can be tested with vartest2
% miu1-miu2 -> can be tested with z_test_2 or ttest2
