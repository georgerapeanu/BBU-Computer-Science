n = input("Please input n: ");
p = input("Please input p: ");
X = 0:1:n;
plot(X, binopdf(X, n, p), 'g');
hold on;
plot(X, normpdf(X, n * p, sqrt(n * p * (1 - p))), 'r');
hold on;
plot(X, poisspdf(X, n * p), 'b');