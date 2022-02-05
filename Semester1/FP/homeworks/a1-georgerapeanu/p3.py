#!/usr/bin/python3
# Solve the problem from the third set here

"""
@author: Rapeanu George - Alexandru

14. Determine the n-th element of the sequence 1,2,3,2,2,5,2,2,3,3,3,7,2,2,3,3,3,... obtained from the sequence of natural numbers by replacing composed numbers with their prime divisors, each divisor d being written d times, without memorizing the elements of the sequence.
"""

def nth_element_of_sequence(n):
  """calculates the nth element of the sequence given by replacing composite numbers with their prime factors(each factor p being written p times)

  Given a strictly positive integer n, this function returns the nth value in the sequence described above
  n: positive integer
  returns: positive integer
  """
  
  current = 1;

  while True:
    d = 2;
    backup_current = current;

    while d * d <= current:
      if current % d == 0:
        if n <= d:
          return d
        n -= d
        while current % d == 0:
          current = current // d
      d += 1
    
    if current == backup_current: #original was not a composite number
      if n == 1:
        return current
      n -= 1
    elif current > 1:
      if n <= current:
        return current
      n -= current
    
    current = backup_current
    current += 1
    


def test_nth_element_of_sequence():
  expected_answers = [1,2,3,2,2,5,2,2,3,3,3,7,2,2,3,3,3]
  for i in range(0,len(expected_answers)):
    assert(nth_element_of_sequence(i + 1) == expected_answers[i])

if __name__ == '__main__':
  test_nth_element_of_sequence()
