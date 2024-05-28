function [z, ni] = bisect(f, a, b, err = 1e-6, nmax = 50)
  z = a;
  ni = 0;
  do 
    ni += 1;
    mid = (a + b) / 2;
    mid_val = f(mid);
    a_val = f(a);
    b_val = f(b);
    
    if(mid_val < 0)
      if(a_val > 0)
        b = mid;
      else 
        a = mid;
      end
    else 
      if(a_val > 0)
        a = mid;
      else 
        b = mid;
      endif
    endif
   until (abs(mid_val) <= err || ni >= nmax )
   
   ni = ni;
   z = mid;
 endfunction