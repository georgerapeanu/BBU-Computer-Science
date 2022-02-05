#!/usr/bin/python3

#@author: Rapeanu George

def create_contestant(scores):
  """ This function creates a contestant entry
    
    given the scores in a list, this function creates a contestant entry structure

    scores: list of int
    returns: contestant(contestant structure)
  """

  entry = []
  for x in scores:
    if x < 0 or x > 10:
      raise Exception("Scores should be between 0 and 10 for each problem")
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

  if problem_score < 0 or problem_score > 10:
    raise Exception("Scores should be between 0 and 10 for each problem")

  contestant[problem_id] = problem_score

