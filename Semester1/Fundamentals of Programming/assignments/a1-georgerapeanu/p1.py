#!/usr/bin/python3
# Solve the problem from the first set here

"""
@author: Rapeanu George - Alexandru

4. For a given natural number n find the largest natural number written with the same digits. (e.g. n=3658, m=8653).
"""

def largest_number_with_same_digits(n):
  """Calculates the biggest number obtainable that has the same digits as n
  
  Given n(a non-negative integer), this function returns the biggest integer with the same digits as n
  n: positive integer
  returns: positive integer(the biggest integer with the same digits as n)
  """
  digitList = list(str(n))
  digitList.sort(reverse=True)

  answer = ""

  for x in digitList:
    answer += str(x)

  return int(answer)

def test_largest_number_with_same_digits():
  assert(largest_number_with_same_digits(0) == 0)
  assert(largest_number_with_same_digits(30) == 30)
  assert(largest_number_with_same_digits(1423) == 4321)
  assert(largest_number_with_same_digits(2901) == 9210)
  assert(largest_number_with_same_digits(10002) == 21000)

if __name__ == '__main__':
  test_largest_number_with_same_digits()

