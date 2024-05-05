function answer = rect(f, a, b, m)
  syms x;
  h = (b - a) / m;
  points=((0:(m-1)) + 1/2) * h + a;
  answer = h * eval(sum(subs(f,x, points)));
 endfunction