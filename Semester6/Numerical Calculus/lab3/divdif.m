function out = divdif (x, f)
  n = length(x);
  answer = zeros(n, n);
  answer(:, 1) = f';
  for i = 2:1:n
    curr_diff = diff(answer(:, i - 1));
    answer(1:n-i+1, i) = (curr_diff(1:n-i+1)' ./ (x(i:n) - x(1:n-i+1)));
  endfor;
  out = answer;
endfunction