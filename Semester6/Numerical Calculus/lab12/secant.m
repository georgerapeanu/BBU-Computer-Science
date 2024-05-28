function [z, ni] = secant(f, x0, x1, eps = 1e-6, nmax = 50)
  val_x0 = f(x0);
  val_x1 = f(x1);
  ni = 0;
  
  while(ni < nmax && abs(val_x1) > eps) 
    ni += 1;
    x_next = x1 - val_x1 * (x1 - x0) / (val_x1 - val_x0);
    val_x_next = f(x_next);
    x0 = x1;
    val_x0 = val_x1;
    x1 = x_next;
    val_x1 = val_x_next;
  endwhile 
  
  z = x1;
 endfunction