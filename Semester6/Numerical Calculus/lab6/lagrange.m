function p=lagrange(x, y)
  n = size(x)(2);
  p = [0];
  for i=1:n
    p_local = [1];
    for j=1:n
      if i != j
        p_local = conv(p_local, [1, -x(j)]) / (x(i) - x(j));
      endif
    endfor
    p = p + p_local * y(i);
  endfor
endfunction