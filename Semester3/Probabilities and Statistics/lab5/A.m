X = [20 21 22 23 24 25 26 27;2 1 3 6 5 9 2 2];
Y = [75 76 77 78 79 80 81 82;3 2 2 5 8 8 1 1];

X_REPL = repelem(X(1,:), X(2,:));
Y_REPL = repelem(Y(1,:), Y(2,:));

printf("mean of X is: %4.4f\n", mean(X_REPL));
printf("mean of Y is: %4.4f\n", mean(Y_REPL));

printf("variance of X is: %4.4f\n", var(X_REPL));
printf("variance of Y is: %4.4f\n", var(Y_REPL));
printf("covariance of X, Y is: %4.4f\n", cov(X_REPL, Y_REPL));
printf("correlation coefficient of X, Y is: %4.4f\n", corrcoef(X_REPL, Y_REPL)(1,2));