#!/usr/bin/python3
# Solve the problem from the second set here

"""
@author: Rapeanu George - Alexandru

8. Find the smallest number m from the Fibonacci sequence, defined by f[0]=f[1]=1, f[n]=f[n-1] + f[n-2], for n > 2, larger than the given natural number n. (e.g. for n = 6, m = 8).
"""

def next_fibonacci_number(n):
  """Calculates the first fibonacci number stricly larger than n

  Given an integer n, this function calculates the smallest integer m that appears in the fibonacci sequence and is strictly larger than n
  n: integer
  returns: integer(the smallest fibonacci number bigger than n)
  """

  if n < 1:
    return 1
  
  a,b = 1,1

  while b <= n:
    a,b = b,a + b

  return b

def test_next_fibonacci_number():
  assert(next_fibonacci_number(-2) == 1)
  assert(next_fibonacci_number(0) == 1)
  assert(next_fibonacci_number(1) == 2)
  assert(next_fibonacci_number(2) == 3)
  assert(next_fibonacci_number(14) == 21)

if __name__ == "__main__":
  test_next_fibonacci_number()
