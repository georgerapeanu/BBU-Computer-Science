n = input("Please enter n: ");
p = input("Please enter p: ");
X = 0:1:n;
XX = 0:0.01:n;
Y_pdf = binopdf(X, n, p);
YY_cdf = binocdf(XX, n, p);
# 'hold on' can be used to prevent wiping the graph
plot(X, Y_pdf, "*", XX, YY_cdf);