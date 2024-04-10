p = lagrange(1980:10:2020, [4451, 5287, 6090, 6970, 7821]);
printf("Aproximation for 2005 is %.4f, difference %.4f\n", polyval(p, 2005), abs(6474 - polyval(p, 2005)));
printf("Aproximation for 2005 is %.4f, difference %.4f\n", polyval(p, 2015), abs(7405 - polyval(p, 2015)));