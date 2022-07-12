#!/usr/bin/python3

#@author: Rapeanu George

import Contestant
import Functions
import UI
import re

def parse_command(s):
  """given a command this function parses it to retirieve the important information
     
     s: string
     returns tuple containing the function responsible for processing it and its own parameters(with no contestants list)
     raises exception if command invalid

     returns tuple
  """

  expresions = [
    "^ *add +-?[0-9]+ +-?[0-9]+ +-?[0-9]+ *$",
    "^ *insert +-?[0-9]+ +-?[0-9]+ +-?[0-9]+ +at +[0-9]+ *$",
    "^ *remove +-?[0-9]+ *$",
    "^ *remove +-?[0-9]+ +to +-?[0-9]+ *$",
    "^ *replace +-?[0-9]+ +(P1|P2|P3) +with +-?[0-9]+ *$",
    "^ *list *$",
    "^ *list +sorted *$",
    "^ *list +(<|=|>) +-?[0-9]+([.][0-9]+)? *$",
    "^ *help *$",
    "^ *exit *$",
    "^ *avg +[0-9]+ +to +[0-9]+ *$",
    "^ *min +[0-9]+ +to +[0-9]+ *$",
    "^ *remove +(<|=|>) +-?[0-9]+([.][0-9]+)? *$",
    "^ *top +[0-9]+ *$",
    "^ *top +[0-9]+ +(P1|P2|P3) *$",
    "^ *undo *$"
  ]
  
  s = s.strip()
  args = s.split(" ")
  args = list(filter(lambda x:len(x) > 0,args))

  if re.match(expresions[0],s) != None:
    contestant = Contestant.create_contestant([int(args[1]),int(args[2]),int(args[3])])
    return Functions.insert_contestant,(contestant,None)
  elif re.match(expresions[1],s) != None:
    contestant = Contestant.create_contestant([int(args[1]),int(args[2]),int(args[3])])
    return Functions.insert_contestant,(contestant,int(args[5]))
  elif re.match(expresions[2],s) != None:
    return Functions.remove_range_contestants,(int(args[1]),int(args[1]))
  elif re.match(expresions[3],s) != None:
    return Functions.remove_range_contestants,(int(args[1]),int(args[3]))
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
    return Functions.replace_contestant,(int(args[1]),problem_id,int(args[4]))
  elif re.match(expresions[5],s) != None:
    return Functions.list_contestants,(None,None)
  elif re.match(expresions[6],s) != None:
    return Functions.list_contestants,(lambda x: -Contestant.get_score(x,None),None)
  elif re.match(expresions[7],s) != None:
    func = None;
    score = float(args[2])
    if args[1] == '<':
      func = (lambda x: (Contestant.get_score(x,None) < score * 3))
    elif args[1] == '=':
      func = (lambda x: (Contestant.get_score(x,None) == score * 3))
    else:
      func = (lambda x: (Contestant.get_score(x,None) > score * 3))
    return Functions.list_contestants,(None,func)
  elif re.match(expresions[8],s) != None:
    return UI.print_help_prompt,()
  elif re.match(expresions[9],s) != None:
    return exit,tuple([0])
  elif re.match(expresions[10],s) != None:
    return Functions.calculate_function,(lambda x:Contestant.get_score(x,None) / 3,(lambda x: sum(x) / len(x)),int(args[1]),int(args[3]))
  elif re.match(expresions[11],s) != None:
    return Functions.calculate_function,(lambda x:Contestant.get_score(x,None) / 3,min,int(args[1]),int(args[3]))
  elif re.match(expresions[12],s) != None:
    func = None;
    score = float(args[2])
    if args[1] == '<':
      func = (lambda x: (Contestant.get_score(x,None) < score * 3))
    elif args[1] == '=':
      func = (lambda x: (Contestant.get_score(x,None) == score * 3))
    else:
      func = (lambda x: (Contestant.get_score(x,None) > score * 3))
    return Functions.remove_filter_contestants,tuple([func])
  elif re.match(expresions[13],s) != None:
    return Functions.top_contestants,(int(args[1]),(lambda x: -Contestant.get_score(x,None)))  
  elif re.match(expresions[14],s) != None:
    problem_id = -1
    if args[2] == "P1":
      problem_id = 0
    elif args[2] == "P2":
      problem_id = 1
    elif args[2] == "P3":
      problem_id = 2
    return Functions.top_contestants,(int(args[1]),(lambda x: -Contestant.get_score(x,problem_id)))  
  elif re.match(expresions[15],s) != None:
    return Functions.undo,tuple()
  else:
    raise Exception("Specified command does not exist")
  
def run_CLI():
  history = []
  contestants = []

  contestants = Functions.generate_random_contestants(10,23)

  UI.print_help_prompt()
  while True:
    command = UI.fetch_command()
    parsed_command = None
    try:
      parsed_command = parse_command(command)
    except Exception as e:
      UI.print_error(str(e))
      UI.print_help_prompt()
      continue
    
    if parsed_command[0] == exit or parsed_command[0] == UI.print_help_prompt:
      parsed_command[0](*parsed_command[1])
      continue

    try:
      return_value = None
      if parsed_command[0] in [Functions.insert_contestant,
                               Functions.remove_filter_contestants,
                               Functions.remove_range_contestants,
                               Functions.replace_contestant,
                               Functions.undo]:
        return_value = parsed_command[0](history,contestants,*parsed_command[1])
      else:
        return_value = parsed_command[0](contestants,*parsed_command[1])

      if parsed_command[0] in [Functions.list_contestants,Functions.top_contestants]:
        UI.print_contestants(return_value)
      elif parsed_command[0] in [Functions.calculate_function]:
        UI.print_value(return_value)
    except Exception as e:
      UI.print_error(str(e))

if __name__ == "__main__":
  run_CLI()
