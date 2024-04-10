function output = my_first_function(i)
output = NaN; %NaN="not a number"
if i ~= 1 %~= the "not equal to" logical operator
 return
else
 disp('Hello World!'); output = 1;
endif
endfunction