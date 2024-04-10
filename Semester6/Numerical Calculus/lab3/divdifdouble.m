function out = divdifdouble (x, f, d_f)
  n = length(x);
  answer = zeros(2 * n,  2 * n);
  answer(1:2:2*n, 1) = f';
  answer(2:2:2*n, 1) = f';
  answer(1:2:2*n, 2) = d_f';
  answer(2:2:2*n-2, 2) = (diff(f) ./ diff(x))'; 
  z = zeros(2 * n);
  z(1:2:2*n) = x;
  z(2:2:2*n) = x;
  n = 2 * n;
  for i = 3:1:n
    curr_diff = diff(answer(:, i - 1));
    answer(1:n-i+1, i) = (curr_diff(1:n-i+1)' ./ (z(i:n) - z(1:n-i+1)));
  endfor;
  out = answer;
endfunction