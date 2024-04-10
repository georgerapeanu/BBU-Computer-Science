x = [81, 100, 121, 144];
y = [9, 10, 11, 12];
p = lagrange(x, y);

printf("eval at 118 is %.4f, abs diff is %.4f\n", polyval(p, 118), abs(polyval(p, 118) - sqrt(118)));