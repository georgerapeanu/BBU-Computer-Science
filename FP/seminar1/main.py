#!/usr/bin/python3
"""

@author: me obviously

Here should be the problem
Basicly the sum of the first n numbers ... for now
"""


def sum_of_first_n_numbers(n):
  """ Computes sum of first n numbers ... obviously including 0

  Given n, a natural number, the function returns the sum of the first n numbers
  n: positive integer
  return: positive integer(the sum of the first n natural numbers)
  """
  #return sum(range(1,n)) #-> python really can do anything
  sum = 0;
  for i in range(0,n):
    sum += i;
  return sum;

def is_prime(n):
  """ Checks if a given positive integer is prime

  Given n, a natural number, the function returns True if the number is prime or False otherwise
  n: positive integer
  return: boolena(True if n is prime, False otherwise)
  """
  if n == 2:
    return True;
  if n % 2 == 0:
    return False;
  if n < 2:#NO
    return False;
  d = 3
  while d * d <= n:
    if n % d == 0:
      return False;
    d += 2;
  return True;

def gcd(a,b):
  while b != 0:
    (a,b) = (b,a % b);
  return a if a > 0 else -a;

def next_prime(n):
  n += 1;
  while is_prime(n) == False:
    n += 1;
  return n;

if __name__ == "__main__":
  print(next_prime(int(input())))
