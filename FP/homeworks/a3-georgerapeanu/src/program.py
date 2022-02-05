#!/usr/bin/python3

#@author: Rapeanu George

from copy import deepcopy
import re
import traceback
import random

"""
  Write non-UI functions below
"""

def create_contestant(scores):
  """ This function creates a contestant entry
    
    given the scores in a list, this function creates a contestant entry structure

    scores: list of int
    returns: contestant(contestant structure)
  """

  entry = []
  for x in scores:
    entry.append(x)

  return entry

def get_score(contestant,problem_id):
  """this function returns the score obtained by a contestant at the problems
     specified by id. If id is None, it returns the total score on all problems
    
     contestant: the contestant entry we want to perform the query on(contestant)
     problem_id: the id of the problem(int)
     
     returns: score of the contestant on the given query(int)
  """

  if problem_id == None:
    return sum(contestant)
  if problem_id < 0 or problem_id >= len(contestant):
    raise IndexError("problem id out of range")
  return contestant[problem_id]
 
def set_score(contestant,problem_id,problem_score):
  """this function replaces the score of the current contestant on the current id
     with the specified problem_score. Changes do affect the original contestant entry

     contestant: the contestant entry we want to update(contestant)
     problem_id: the id of the problem(int)
     problem_score: the new problem score(int)
     returns None
  """

  if problem_id < 0 or problem_id >= len(contestant):
    raise IndexError("problem id out of range")

  contestant[problem_id] = problem_score

def generate_random_contestants(n,seed = None):
  """this function generates a list of n random contestants with specified seed

     n:int
     seed: int or None
  """

  ans = []

  rng = random.Random(seed)

  for i in range(0,n):
    ans.append(create_contestant([rng.randint(0,100),rng.randint(0,100),rng.randint(0,100)]))

  return ans

def insert_contestant(contestants,contestant,position = None):
  """inserts the given contestant into the list on specified position.
     if position lies outside the current range throws exception
     if position is None or not specified it inserts the contestant in the back of the list

     contestants: list of contestants
     contestant: contestant
     position: int or None

     returns None
  """
  
  position = (position if position != None else len(contestants))

  if position < 0 or position > len(contestants):
    raise Exception("Position outside of current list range")
  
  contestants.append(create_contestant([]))
  
  i = len(contestants) - 1

  while(i > position):
    contestants[i] = contestants[i - 1]
    i -= 1
  
  contestants[position] = contestant

def remove_contestants(contestants,left_position,right_position):
  """removes the contestants from the range left_position...right_position from the current list
     raises exception if positions lie outside of range or do not specify a valid interval
     
     contestants: list of contestants
     left_position: int
     right_position: int

     returns None
  """

  if left_position < 0 or right_position >= len(contestants) or left_position > right_position:
    raise Exception("Invalid range")
  
  contestants[:] = contestants[:left_position] + contestants[right_position + 1:]
  
def replace_contestant(contestants,position,problem_id,new_score):
  """replaces the score of the contestant on the specified position with the new specified score
     raises exception if no contestant has the specified position
     inherits the exception raised by set_score
     
     contestants: list of contestants
     position: int
     problem_id: int
     new_score: int

     returns None
  """
  
  if position < 0 or position >= len(contestants):
    raise Exception("position outside of range")

  set_score(contestants[position],problem_id,new_score)

      

def list_contestants(contestants,__mapping = None,__filter = None):
  """given a mapping function(for sorting or None if no sorting required) and
     a filter function(for filtering only desired contestants), it returns a list
     containing the valid contestants

     contestants: list of contestants
     __mapping: map function
     __filter: filter function

     returns list of contestants
  """
  
  ans = deepcopy(contestants)
  if __filter != None:
    ans = list(filter(__filter,ans))
  if __mapping != None:
    ans.sort(key=__mapping)
 
  return ans
 
def parse_command(s):
  """given a command this function parses it to retirieve the important information
     
     s: string
     returns tuple containing the function responsible for processing it and its own parameters(with no contestants list)
     raises exception if command invalid

     returns tuple
  """

  #TODO add posibility for validation and fix mandatory spaces for regex
  expresions = [
    "^ *add *-?[0-9]+ *-?[0-9]+ *-?[0-9]+ *$",
    "^ *insert *-?[0-9]+ *-?[0-9]+ *-?[0-9]+ *at *[0-9]+ *$",
    "^ *remove *-?[0-9]+ *$",
    "^ *remove *-?[0-9]+ *to *-?[0-9]+ *$",
    "^ *replace *-?[0-9]+ *(P1|P2|P3) *with *-?[0-9]+ *$",
    "^ *list *$",
    "^ *list *sorted*$",
    "^ *list *(< | = | >) *-?[0-9]+([.][0-9]+)? *$",
    "^ *help *$",
    "^ *exit *$"
  ]
  
  s = s.strip()
  args = s.split(" ")
  args = list(filter(lambda x:len(x) > 0,args))

  if re.match(expresions[0],s) != None:
    contestant = create_contestant([int(args[1]),int(args[2]),int(args[3])])
    return insert_contestant,(contestant,None)
  elif re.match(expresions[1],s) != None:
    contestant = create_contestant([int(args[1]),int(args[2]),int(args[3])])
    return insert_contestant,(contestant,int(args[5]))
  elif re.match(expresions[2],s) != None:
    return remove_contestants,(int(args[1]),int(args[1]))
  elif re.match(expresions[3],s) != None:
    return remove_contestants,(int(args[1]),int(args[3]))
  elif re.match(expresions[4],s) != None:
    problem_id = 0
    if args[2] == "P1":
      problem_id = 0
    elif args[2] == "P2":
      problem_id = 1
    elif args[2] == "P3":
      problem_id = 2
    else:
      raise Exception("Specified problem does not exist")
    return replace_contestant,(int(args[1]),problem_id,int(args[4]))
  elif re.match(expresions[5],s) != None:
    return list_contestants,(None,None)
  elif re.match(expresions[6],s) != None:
    return list_contestants,(lambda x: -get_score(x,None),None)
  elif re.match(expresions[7],s) != None:
    func = None;
    score = float(args[2])
    if args[1] == '<':
      func = (lambda x: (get_score(x,None) < score * 3))
    elif args[1] == '=':
      func = (lambda x: (get_score(x,None) == score * 3))
    else:
      func = (lambda x: (get_score(x,None) > score * 3))
    return list_contestants,(None,func)
  elif re.match(expresions[8],s) != None:
    return print_help_prompt,()
  elif re.match(expresions[9],s) != None:
    return exit,tuple([0])
  else:
    raise Exception("Specified command does not exist")
  

"""
  Testing area
"""

def has_exception(function,args):
  try:
    function(*args)
  except Exception:
    return True
  return False

def test_get_score():
  contestant = create_contestant([10,30,20])
  assert(get_score(contestant,0) == 10)
  assert(get_score(contestant,1) == 30)
  assert(get_score(contestant,2) == 20)
  assert(get_score(contestant,None) == 60)

def test_set_score():
  contestant = create_contestant([10,30,20])
  set_score(contestant,0,20)
  assert(get_score(contestant,0) == 20)
  assert(get_score(contestant,1) == 30)
  assert(get_score(contestant,2) == 20)
  assert(get_score(contestant,None) == 70)

def test_insert_contestant():
  contestants = [create_contestant([10,0,0]),create_contestant([20,10,4])]
  
  assert(has_exception(insert_contestant,(contestants,create_contestant([0,0,0]),-1)) == True)
  
  assert(has_exception(insert_contestant,(contestants,create_contestant([0,0,0]),3)) == True)

  insert_contestant(contestants,create_contestant([0,0,0]))
  assert(contestants == [create_contestant([10,0,0]),create_contestant([20,10,4]),create_contestant([0,0,0])])
  insert_contestant(contestants,create_contestant([1,1,1]),2)
  assert(contestants == [create_contestant([10,0,0]),create_contestant([20,10,4]),create_contestant([1,1,1]),create_contestant([0,0,0])])

def test_remove_contestants():
  contestants = [create_contestant([10,0,0]),
                 create_contestant([20,10,4]),
                 create_contestant([21,10,4]),
                 create_contestant([23,10,4]),
                ]
  
  assert(has_exception(remove_contestants,(contestants,-1,2)) == True)
  assert(has_exception(remove_contestants,(contestants,0,10)) == True)
  assert(has_exception(remove_contestants,(contestants,3,2)) == True)


  remove_contestants(contestants,1,2)
  assert(contestants == [create_contestant([10,0,0]),create_contestant([23,10,4])])

def test_replace_contestant():
  contestants = [create_contestant([10,0,0]),
                 create_contestant([20,10,4]),
                 create_contestant([21,10,4]),
                 create_contestant([23,10,4]),
                ]
  
  assert(has_exception(replace_contestant, (contestants,-1,0,0)) == True)
  assert(has_exception(replace_contestant, (contestants,100,10,10)) == True)
  replace_contestant(contestants,0,1,10)
  assert (contestants == [create_contestant([10,10,0]),
                          create_contestant([20,10,4]),
                          create_contestant([21,10,4]),
                          create_contestant([23,10,4])])

def test_list_contestants():
  contestants = [create_contestant([10,0,0]),
                 create_contestant([20,10,4]),
                 create_contestant([21,10,4]),
                 create_contestant([23,10,4]),
                ]
  assert(list_contestants(contestants,None,None) == \
                [create_contestant([10,0,0]),
                 create_contestant([20,10,4]),
                 create_contestant([21,10,4]),
                 create_contestant([23,10,4]),
                ])
  
  assert(list_contestants(contestants,lambda x: -get_score(x,None),None) == \
                [
                 create_contestant([23,10,4]),
                 create_contestant([21,10,4]),
                 create_contestant([20,10,4]),
                 create_contestant([10,0,0]),
                ])
  
  assert(list_contestants(contestants,None,lambda x: get_score(x,None) > 20) == \
                [
                 create_contestant([20,10,4]),
                 create_contestant([21,10,4]),
                 create_contestant([23,10,4]),
                ])
  assert(list_contestants(contestants,lambda x: -get_score(x,None),lambda x: get_score(x,None) > 20) == \
                [
                 create_contestant([23,10,4]),
                 create_contestant([21,10,4]),
                 create_contestant([20,10,4]),
                ])

def test_parse_command():
  assert(parse_command(" add 10 20  10  ") == (insert_contestant,(create_contestant([10,20,10]),None))) 
  assert(parse_command(" insert  10 20  10  at 2") == (insert_contestant,(create_contestant([10,20,10]),2))) 
  assert(parse_command("remove  10") == (remove_contestants,(10,10))) 
  assert(parse_command("remove  10 to 12") == (remove_contestants,(10,12))) 
  assert(parse_command("replace  10 P2 with 200") == (replace_contestant,(10,1,200))) 
  assert(parse_command("list") == (list_contestants,(None,None)))


def run_tests():
  test_get_score()
  test_set_score()
  test_insert_contestant()
  test_remove_contestants()
  test_replace_contestant()
  test_list_contestants()
  test_parse_command()

"""
  Write the command-driven UI below
"""

def print_error(s):
  print("Error: %s" %s)

def print_help_prompt():
  print("Usage:\n")
  print("add <P1 score> <P2 score> <P3 score>")
  print("\tadds a contestant with the specified scores to the back of the current list")
  print("insert <P1 score> <P2 score> <P3 score> at <position>")
  print("\tadds a contestant with the specified scores at the specified position")
  print("remove <position>")
  print("\tremoves contestant that is at position")
  print("remove <start position> to <end position>")
  print("\tremoves contestant that is in given range")
  print("replace <position> <P1 | P2 | P3> with <new score>")
  print("\treplaces the score of the contestant on the specified position at the specified problem with the new score")
  print("list")
  print("\tprints the current contestants")
  print("list sorted")
  print("\tprints the current contestant list sorted decreasingly by their average/total score")
  print("list [ < | = | > ] <score>")
  print("\tprints the contestants which respect the given criterion")
  print("help")
  print("\tdisplays help prompt")
  print("exit")
  print("\tcloses the application")


def print_contestant(contestant):
  print("scores: ",end="")
  for i in range(0,3):
    print(get_score(contestant,i),end=" ")
  print("average score: %f" % (get_score(contestant,None) / 3))

def print_contestants(contestants):
  for contestant in contestants:
    print_contestant(contestant)

def run_CLI():
  contestants = []

  contestants = generate_random_contestants(10,23)

  print_help_prompt()
  while True:
    command = input("Enter your command:")
    parsed_command = None
    try:
      parsed_command = parse_command(command)
    except Exception as e:
      print_error(str(e))
      print_help_prompt()
      continue
    
    if parsed_command[0] == exit or parsed_command[0] == print_help_prompt:
      parsed_command[0](*parsed_command[1])
      continue

    return_value = parsed_command[0](contestants,*parsed_command[1])
    if parsed_command[0] == list_contestants:
      print_contestants(return_value)

run_tests()
run_CLI()

