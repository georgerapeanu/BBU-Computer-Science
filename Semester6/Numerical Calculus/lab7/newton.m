function p = newton (x_range, t_values)
  n=size(x_range)(2);
  p = sym(n);
  syms x;
  x_prod = cat(1, [1], cumprod(x - x_range)) ;
  div_dif = (divdif(x_range, t_values)(1, :))';
  for i=1:n 
    p(i) = simplify(x_prod(1:i) * div_dif(1:i));
  endfor
endfunction