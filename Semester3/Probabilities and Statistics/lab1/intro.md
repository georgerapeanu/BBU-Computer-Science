# Laboratory 1

Basic syntax

```
a = 2 #variable
b = 3
c = a * b
d = a + b

A = [1 2 3 4 5]             # vector
B = -10:1:10                # range from -10 to 10 with step 1, also vector
C = [1 2 3; 4 5 6; 7 8 9]   # matrix

C(1:2, 2:3)                 # submatrix
D = [1 1 1; 1 1 1; 1 1 1]
C * D                       # matrix multiplication
C .* D                      # pointwise multiplication
C .^ k                      # pointwise raise to power of k
C ^ k                       # k'th power of matrix C

help f                      # displays a help text for function f(for example zeros)


# function with no return value
function functionName(function args) 
    functionBody
endfunction

# function with return value
function retvalue = functionName(function args) 
    functionBody
endfunction

# function with multiple return values
function [ret1, ret2, ...] = functionName(function args) 
    functionBody
endfunction
# functions can be exported in .m files and used if they share the same name as the file

help(plot)

```

## **Files can be saved as .m files**