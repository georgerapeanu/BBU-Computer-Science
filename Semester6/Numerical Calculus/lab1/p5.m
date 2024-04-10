function out = p5(n)
   out = 1;
   for step = 1:1:n
      disp(step)
      out = 1 + 1 / (out + 1);
      disp(out)
   endfor
   
endfunction