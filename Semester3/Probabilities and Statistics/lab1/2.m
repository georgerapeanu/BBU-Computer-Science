x=-1:0.1:1
plot(x, x.^5/10, x, x.*sin(x), x, cos(x))
title("Multiple plots")
legend("x^5/10", "xsinx", "cosx")