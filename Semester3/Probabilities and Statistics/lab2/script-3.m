%%%% This guy likes prints and explanations for the example
%%%% pretty prints to, for example print("The probability for... is...")

%a) Bino(3, 0.5)
%P(X=0) = bionpdf(0, 3, 0.5)
%X:
%  0   1   2   3
% 1/8 3/8 3/8 1/8
binopdf(0:1:3, 3, 0.5)
%b)
binocdf(0:1:3, 3, 0.5)

%c)
%P(X = 0)
binopdf(0, 3, 0.5)
%P(X != 1)
1 - binopdf(1, 3, 0.5)
%d)
%P(X <= 2)
binocdf(2, 3, 0.5)
%P(X < 2)
binocdf(1, 3, 0.5)

%e)
%P(X >= 1)
1 - binocdf(0, 3, 0.5)
%P(X > 1)
1 - binocdf(1, 3, 0.5)
%f)

%ans = 0;
%for i = 1:3
%  ans += (rand() <= 0.5);
%endfor
%printf("The result is %d", ans);

N = input("N? ");
C = rand(3, N);
Y = (C < 0.5);
X = sum(Y);
hist(X);