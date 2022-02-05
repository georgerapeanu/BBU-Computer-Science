#!/usr/bin/python3
#@author: Rapeanu George - Alexandru
# Write the implementation for A2 in this file
#

import random
from copy import deepcopy

# UI section
# (write all functions that have input or print statements here). 
# Ideally, this section should not contain any calculations relevant to program functionalities

def print_error(s):
  """prints the given error

  s: string
  returns: None
  """
  print("Error: " + s)

def read_operation():
  """reads operation from input and ignores whitespace
  returns: string
  """

  return input("Please enter operation: ").strip().replace(' ','')

def display_help_prompt():
  """This function displays the help prompt

  """
  print("Usage:")
  print("1. Read a complex number from stdin")
  print("\t the number should respect normal mathematical notation")
  print("\t in case it is invalid, an error will appear on the screen")
  print("2. Write complex numbers from memory")
  print("\t displays the complex numbers committed to memory in normal mathematical notation")
  print("3. displays to console the longest sequence that respects a given propriety")
  print("\t the operation should be specified by its index in README.md(currently only 3 & 9 are supported)")
  print("\t in case the operation is not supported or is invalid, an error will appear on the screen")
  print("4. Exit")
  return 

def read_complex_number():
  """This function reads a complex number from stdin
    
    returns: complex number if successfull, None otherwise
  """
  s = input("z=")

  if check_valid_complex_number(s) == False:
    print_error("invalid complex number")
    return None
  
  return string_to_complex_number(s)

def display_complex_numbers(numbers):
  """This function displays the given complex numbers to stdout

  given a list of complex numbers, this function displays them on stdout

  numbers: list of complx numbers

  returns: None
  """
  for x in numbers:
    print(complex_number_to_string(x))

def run_menu(numbers):
  
  display_help_prompt()
  while True:
    command = input("Please enter command: ")
    
    if command == "1":
      insert_complex_number(numbers)
    elif command == "2":
      display_complex_numbers(numbers)
    elif command == "3":
      tmp = get_longest_sequence(numbers)
      if tmp is None:
        print_error("operation invalid or unsupported")
        continue
      display_complex_numbers(tmp)
    elif command == "4":
      exit(0)
    else:
      print_error("invalid operation")
      display_help_prompt()

# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values

# print('Hello A2'!) -> prints aren't allowed here!

def create_complex_number(real,imag):
  """this function creates a complex number

  given the real and the imaginary part of a complex number, this function returns the complex number as a tuple
  
  real: integer
  imag: integer
  
  returns complex number(tuple(int,int))
  """
  return (real,imag)

def get_real(z):
  """this function returns the real part of a complex number

  given a complex number, this function returns the real part of a complex number

  z: complex number

  returns: real part(int)
  """

  return z[0]

def get_imag(z):
  """this function returns the imaginary part of a complex number

  given a complex number, this function returns the imaginary part of a complex number

  z: complex number

  returns: imaginary part(int)
  """

  return z[1]

def add_complex_numbers(a,b):
  """this function adds two complex numbers

  given two complex numbers, this function returns the sum of those complex numbers
  a: complex number
  b: complex number

  returns: complex number
  """
  return create_complex_number(get_real(a) + get_real(b), get_imag(a) + get_imag(b))

def get_modulus_squared(z):
  """this function returns the modulus raised to the power of 2 of a complex number

  given a complex number, this function returns the modulus of that number raised to the power of 2

  z: complex number

  returns: modulus squared(int)
  """

  return get_real(z) ** 2 + get_imag(z) ** 2

def check_valid_complex_number(s):
  """this function checks if given s is a valid complex number

  given a string, this function checks if it respects the rules for it to be considered a valid complex number
  ignores whitespace

  s: string

  returns valid(boolean)
  """

  s = s.strip().replace(' ','')

  if len(s) == 0:
    return False

  #basic rules for valid complex number
  #1. only chars allowed are digits(0-9), + and - operators, and i
  #2. must contain at most one i
  #3. must contain at most 2 operators
  #4. in case the is an i, it should be on the last string position
  #5. in case of 2 operators first one should be on the first string position
  #6. each operator must be responsible for a non empty substring
  #7. in case of 2 parts second one should contain i

  cnt_operators = 0
  cnt_i = 0;

  operators_positions = []

  #1. only chars allowed are digits(0-9), + and - operators, and i
  for i in range(0,len(s)):
    if ord('0') <= ord(s[i]) and ord(s[i]) <= ord('9'):
      continue
    if s[i] == '+' or s[i] == '-':
      cnt_operators += 1
      operators_positions.append(i)
      continue;
    if s[i] == 'i':
      cnt_i += 1
      continue
    return False
  
  #2. must contain at most one i
  #3. must contain at most 2 operators
  if cnt_operators > 2 or cnt_i > 1:
    return False
  
  #4. in case the is an i, it should be on the last string position
  if cnt_i == 1 and s.find('i') != len(s) - 1:
    return False

  #5. in case of 2 operators first one should be on the first string position
  if cnt_operators == 2 and operators_positions[0] != 0:
    return False
  
  #6. each operator must be responsible for a non empty substring
  for x in operators_positions:
    if x + 1 == len(s) or s[x + 1] == '+' or s[x + 1] == '-':
      return False

  
  #7. in case of 2 parts second one should contain i
  if cnt_operators > 0 and operators_positions[-1] != 0 and cnt_i == 0:
    return False

  return True;

def test_check_valid_complex_number():
  assert(check_valid_complex_number("") == False);
  assert(check_valid_complex_number("++i") == False);
  assert(check_valid_complex_number("-+i") == False);
  assert(check_valid_complex_number("-0+i") == True);
  assert(check_valid_complex_number("-i") == True);
  assert(check_valid_complex_number("2+3") == False);
  assert(check_valid_complex_number("2+3i") == True);
  assert(check_valid_complex_number("2-3i") == True);
  assert(check_valid_complex_number("-2+3i") == True);
  assert(check_valid_complex_number("-23i") == True);
  assert(check_valid_complex_number("+23") == True);
  assert(check_valid_complex_number("+23+0i") == True);
  assert(check_valid_complex_number("+23-0i") == True);
  assert(check_valid_complex_number("    ") == False);
  assert(check_valid_complex_number("+ +  i") == False);
  assert(check_valid_complex_number("- +i") == False);
  assert(check_valid_complex_number("-0 + i") == True);
  assert(check_valid_complex_number(" -  i") == True);
  assert(check_valid_complex_number("2 +3") == False);
  assert(check_valid_complex_number("2+ 3 i") == True);
  assert(check_valid_complex_number("2- 3i") == True);
  assert(check_valid_complex_number("-2+3i ") == True);
  assert(check_valid_complex_number("-  2 3    i") == True);
  assert(check_valid_complex_number("+2 3") == True);
  assert(check_valid_complex_number("+ 23 +0i") == True);
  assert(check_valid_complex_number("+23 - 0i") == True);
  
def string_to_complex_number(s):
  """this function takes a string and converts it to a complex number

  given a string that contains a valid complex number in the form a +/- bi, this function returns a tuple containing the complex number
  
  ignores whitespace

  s: string

  returns complex number
  """
  
  s = s.strip().replace(' ','')
  
  if s[0] != '-' and s[0] != '+':
    s = "+" + s

  operators_positions = []

  for i in range(0,len(s)):
    if s[i] == '+' or s[i] == '-':
      operators_positions.append(i)
  
  real = 0
  imag = 0

  if len(operators_positions) == 1:
    if s[-1] == 'i':
      imagStr = s[operators_positions[0] + 1:len(s) - 1]
      if imagStr == "":
        imagStr = "1"
      imag = int(imagStr)
      if s[operators_positions[0]] == '-':
        imag = -imag
    else:
      real = int(s[operators_positions[0] + 1:len(s)]) 
      if s[operators_positions[0]] == '-':
        real = -real
  else:
    real = int(s[operators_positions[0] + 1:operators_positions[1]])
    imagStr = s[operators_positions[1] + 1:len(s) - 1]
    if imagStr == "":
      imagStr = "1"
    imag = int(imagStr)

    if s[operators_positions[0]] == '-':
      real = -real
    if s[operators_positions[1]] == '-':
      imag = -imag
    
  return create_complex_number(real,imag)

def test_string_to_complex_number():
  assert(string_to_complex_number("-0+i") == create_complex_number(0,1));
  assert(string_to_complex_number("-i") == create_complex_number(0,-1));
  assert(string_to_complex_number("2+3i") == create_complex_number(2,3));
  assert(string_to_complex_number("2-3i") == create_complex_number(2,-3));
  assert(string_to_complex_number("-2+3i") == create_complex_number(-2,3));
  assert(string_to_complex_number("-23i") == create_complex_number(0,-23));
  assert(string_to_complex_number("+23") == create_complex_number(23,0));
  assert(string_to_complex_number("+23+0i") == create_complex_number(23,0));
  assert(string_to_complex_number("+23-0i") == create_complex_number(23,0));
  assert(string_to_complex_number("-0 + i") == create_complex_number(0,1));
  assert(string_to_complex_number(" -  i") == create_complex_number(0,-1));
  assert(string_to_complex_number("2+ 3 i") == create_complex_number(2,3));
  assert(string_to_complex_number("2- 3i") == create_complex_number(2,-3));
  assert(string_to_complex_number("-2+3i ") == create_complex_number(-2,3));
  assert(string_to_complex_number("-  2 3    i") == create_complex_number(0,-23));
  assert(string_to_complex_number("+2 3") == create_complex_number(23,0));
  assert(string_to_complex_number("+ 23 +0i") == create_complex_number(23,0));
  assert(string_to_complex_number("+23 - 0i") == create_complex_number(23,0));
  assert(string_to_complex_number("+3 - 4i") == create_complex_number(3,-4));
  assert(string_to_complex_number("+4 + 5i") == create_complex_number(4,5));
  assert(string_to_complex_number("+2i") == create_complex_number(0,2));
  assert(string_to_complex_number("2i") == create_complex_number(0,2));

def complex_number_to_string(z):
  """This function convers a complex number to a string
  
    given a complex number, this function returns the string coresponding to that complex number

    z: complex number
    returns: string
  """

  if get_real(z) == 0:
    if get_imag(z) == 1:
      return "i"
    elif get_imag(z) == -1:
      return "-i"
    else:
      return str(get_imag(z)) + "i"

  if get_imag(z) == 0:
    return str(get_real(z))

  if get_imag(z) < 0:
    if get_imag(z) == -1:
      return str(get_real(z)) + "-i"
    else:
      return str(get_real(z)) + str(get_imag(z)) + "i"
  
  if get_imag(z) == 1:
    return str(get_real(z)) + "+i"

  return str(get_real(z)) + "+" + str(get_imag(z)) + "i"

def test_complex_number_to_string():
  assert(complex_number_to_string(create_complex_number(0,1)) == "i");
  assert(complex_number_to_string(create_complex_number(0,-1)) == "-i");
  assert(complex_number_to_string(create_complex_number(2,3)) == "2+3i");
  assert(complex_number_to_string(create_complex_number(2,-3)) == "2-3i");
  assert(complex_number_to_string(create_complex_number(-2,3)) == "-2+3i");
  assert(complex_number_to_string(create_complex_number(0,-23)) == "-23i");
  assert(complex_number_to_string(create_complex_number(23,0)) == "23");
  assert(complex_number_to_string(create_complex_number(3,-4)) == "3-4i");
  assert(complex_number_to_string(create_complex_number(4,5)) == "4+5i");
  assert(complex_number_to_string(create_complex_number(0,2)) == "2i");

def insert_complex_number(numbers):
  """This function inserts into the given list the complex number read from stdin, if valid

  Given a lsit of complex numbers, this function appends to the list the new number from stdin

  numbers: list of complex numbers

  returns: None
  """
  z = read_complex_number()
  if z is None:
    return None
  numbers.append(z)

#3. Numbers having the same modulus.
def get_sequence_3(numbers):
  """this function returns the longest sequence of numbers that respect propriety 3
    given a list of complex numbers, returns the longest sequence of numbers that respect propriety 3

    numbers: list of complex numbers
    returns: list of complex numbers
  """

  fr = {} 

  for z in numbers:
    modulus_squared = get_modulus_squared(z) #using modulus squared in order to avoid floating point errors
    if modulus_squared not in fr:
      fr[modulus_squared] = 0
    fr[get_modulus_squared(z)] += 1 

  best_modulus_squared, best_length = 0,-1
  answer = []

  for x in fr:
    if fr[x] > best_length:
      best_length = fr[x]
      best_modulus_squared = x
  
  for z in numbers:
    if get_modulus_squared(z) == best_modulus_squared:
      answer.append(z)

  return answer

def test_get_sequence_3():
  assert(                                             \
    get_sequence_3([create_complex_number(1,0),       \
                    create_complex_number(2,3),       \
                    create_complex_number(-1,2),      \
                    create_complex_number(-1,-1),     \
                    create_complex_number(0,1)]) == [create_complex_number(1,0), create_complex_number(0,1)]
  )
  assert(get_sequence_3([]) == [])

#Consecutive number pairs have equal sum. (e.g. 1+3i, 1-i, 1+3i, 1-i)
def get_sequence_9(numbers):
  """this function returns the longest sequence of numbers that respect propriety 9
    given a list of complex numbers, returns the longest sequence of numbers that respect propriety 9

    numbers: list of complex numbers
    returns: list of complex numbers
  """
  dp = {}

  for i in range(len(numbers) - 1,-1,-1):
    found_same = False;
    for j in range(i + 1,len(numbers)):
      if numbers[i] == numbers[j]:
        found_same = True
        continue
      if (numbers[i],numbers[j]) not in dp:
        dp[(numbers[i],numbers[j])] = 2
      if dp[(numbers[i],numbers[j])] < (dp[(numbers[j],numbers[i])] if (numbers[j],numbers[i]) in dp else 0) + 1:
        dp[(numbers[i],numbers[j])] = dp[(numbers[j],numbers[i])] + 1
    
    if found_same == True:
      if (numbers[i],numbers[i]) not in dp:
        dp[(numbers[i],numbers[i])] = 2
      else:
        dp[(numbers[i],numbers[i])] += 1
 
  best = 0
  seq = (0,0)

  for x in dp:
    if dp[x] > best:
      best = dp[x]
      seq = x
  
  answer = []

  for i in range(0,best):
    answer.append(seq[0])
    seq = (seq[1],seq[0])

  return answer

def check_valid_sequence_9(sequence,desired_length):
  """ this function is used for testing, it checks if the returned sequence is valid and if it has the best length
  
      sequence: list of complex numbers
      desired_length: int

      returns boolean
  """
  if len(sequence) != desired_length:
    return False

  if len(sequence) <= 1:
    return True

  target_sum = add_complex_numbers(sequence[0], sequence[1])

  for i in range(0,len(sequence) - 1):
    if add_complex_numbers(sequence[i], sequence[i + 1]) != target_sum:
      return False

  return True

def test_get_sequence_9():
  assert(                                                                    \
    check_valid_sequence_9(get_sequence_9([create_complex_number(1,0),       \
                    create_complex_number(-1,2),                             \
                    create_complex_number(2,3),                              \
                    create_complex_number(-1,-1),                            \
                    create_complex_number(-1,2)]),3)
  ) 
  assert(get_sequence_9([]) == [])
  assert(                                                                    \
    check_valid_sequence_9(get_sequence_9([create_complex_number(1,0),       \
                    create_complex_number(1,0),                              \
                    create_complex_number(1,0),                              \
                    create_complex_number(1,0),                              \
                    create_complex_number(1,0)]),5)
  )

def get_longest_sequence(numbers):
  """This function displays the longest sequence that observes a given propriety
  
  returns None if operation invalid, or a list of complex numbers if it succeeded
  """

  operation = read_operation()

  if operation == "3":
    return get_sequence_3(numbers)
  elif operation == "9":
    return get_sequence_9(numbers) 
  else:
    return None

def run_tests():
  """this functions runs the tests for this script

    returns None
  """
  test_check_valid_complex_number()
  test_string_to_complex_number()
  test_complex_number_to_string()
  test_get_sequence_3()
  test_get_sequence_9()

if __name__ == '__main__':
  run_tests()

  numbers = []
 
  rng = random.Random(23)

  for i in range(0,10):
    numbers.append(create_complex_number(rng.randint(-10,10),rng.randint(-10,10)));

  run_menu(numbers)
