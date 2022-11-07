p = input("Please enter p value:");

for n = 1:10:10000
  x = 0:n;
  plot(x, binopdf(x, n, p));
  pause(0.5);
endfor