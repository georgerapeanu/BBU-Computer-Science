#!/usr/bin/python3

#@author: Rapeanu George

import Contestant
from copy import deepcopy
import random

def generate_random_contestants(n,seed = None):
  """this function generates a list of n random contestants with specified seed

     n:int
     seed: int or None
  """

  ans = []

  rng = random.Random(seed)

  for i in range(0,n):
    ans.append(Contestant.create_contestant([rng.randint(0,10),rng.randint(0,10),rng.randint(0,10)]))

  return ans

def insert_contestant(history,contestants,contestant,position = None):
  """inserts the given contestant into the list on specified position.
     if position lies outside the current range throws exception
     if position is None or not specified it inserts the contestant in the back of the list
     history is necessary for undo

     history: history list
     contestants: list of contestants
     contestant: contestant
     position: int or None

     returns None
  """
  
  position = (position if position != None else len(contestants))

  if position < 0 or position > len(contestants):
    raise Exception("Position outside of current list range")
  
  history.append(deepcopy(contestants))
  contestants.append(Contestant.create_contestant([]))
  
  i = len(contestants) - 1

  while(i > position):
    contestants[i] = contestants[i - 1]
    i -= 1
  
  contestants[position] = contestant

def remove_filter_contestants(history,contestants,__filter):
  """removes the contestants that respect a certain filter
     history is necessary for undo
    
     history: history list
     contestants: list of contestants
     __filter: filter function
  """
  history.append(deepcopy(contestants))
  contestants[:] = [contestant for contestant in contestants if not __filter(contestant)]

def remove_range_contestants(history,contestants,left_position,right_position):
  """removes the contestants from the range left_position...right_position from the current list
     raises exception if positions lie outside of range or do not specify a valid interval
     history is necessary for undo
     
     history: history list
     contestants: list of contestants
     left_position: int
     right_position: int

     returns None
  """

  if left_position < 0 or right_position >= len(contestants) or left_position > right_position:
    raise Exception("Invalid range")
  
  history.append(deepcopy(contestants))
  contestants[:] = contestants[:left_position] + contestants[right_position + 1:]
  
def replace_contestant(history,contestants,position,problem_id,new_score):
  """replaces the score of the contestant on the specified position with the new specified score
     raises exception if no contestant has the specified position
     inherits the exception raised by set_score
     history is necessary for undo

     history: history list
     contestants: list of contestants
     position: int
     problem_id: int
     new_score: int

     returns None
  """
  
  if position < 0 or position >= len(contestants):
    raise Exception("position outside of range")

  history.append(deepcopy(contestants))
  Contestant.set_score(contestants[position],problem_id,new_score)
      

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

def calculate_function(contestants,extractor,function,left,right):
  """calculates the result of function(extractor(contesants[left:right + 1]))
     extractor should be a function that maps each contestant to the object that function operates on(extracts the information we need)
     function should be a function that takes the list of extractor results and composes them

     raises error if range invalid

     contestants: list of contestants
     function: function
     extractor: function
     left: int
     right: int

     returns result of function
  """
  if left < 0 or right >= len(contestants) or left > right:
    raise Exception("Invalid range")

  return function([extractor(contestants[i]) for i in range(left,right + 1)])

def top_contestants(contestants,number,__mapping):
  """returns a list of the first number contestants sorted by a given mapping

     raises error if number is too big(> len(contestants)) or too low(< 0)

     contestants:list of contestants
     number: the size of the returned list
     __mapping: mapping used for sorting
    
    returns list
  """

  if number < 0 or number >= len(contestants):
    raise Exception("Invalid number")

  return list_contestants(contestants,__mapping)[:number]

def undo(history,contestants):
  """undoes the last successful operation that modified the list
     
     raises error if no further undoing can be done

     history: history list
     contestants: list of contestants

     returns: none
  """
  
  if len(history) == 0:
    raise Exception("No further undos are possible")

  contestants[:] = history[-1]
  history[:] = history[:-1]
