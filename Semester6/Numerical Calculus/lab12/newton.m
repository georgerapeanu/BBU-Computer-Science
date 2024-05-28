function [z, ni] = newton(f, f_diff, x0, eps = 1e-6, nmax = 50)
  ni = 0;
  
  while(ni < nmax && abs(f(x0)) > eps) 
    ni += 1;
    x0 = x0 - f(x0) / f_diff(x0);
  endwhile 
  
  z = x0;
 endfunction