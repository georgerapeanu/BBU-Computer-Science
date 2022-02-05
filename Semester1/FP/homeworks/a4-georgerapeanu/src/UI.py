#!/usr/bin/python3

#@author: Rapeanu George

import Contestant

def print_value(x):
  print(x)

def fetch_command():
  return input("Please enter your command: ")

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
  print("remove [ < | = | > ] <score>")
  print("\tremoves contestants that respect the given criterion")
  print("replace <position> <P1 | P2 | P3> with <new score>")
  print("\treplaces the score of the contestant on the specified position at the specified problem with the new score")
  print("list")
  print("\tprints the current contestants")
  print("list sorted")
  print("\tprints the current contestant list sorted decreasingly by their average/total score")
  print("list [ < | = | > ] <score>")
  print("\tprints the contestants which respect the given criterion")
  print("avg <start position> to <end position>")
  print("\tprints the average score of the contestants between the given positions")
  print("min <start position> to <end position>")
  print("\tprints the minimum score of the contestants between the given positions")
  print("top <number>")
  print("\tprints the top <number> contestants sorted decreasingly by their score")
  print("top <number> <P1 | P2 | P3>")
  print("\tprints the top <number> contestants sorted decreasingly by their score on the specified problem")
  print("undo")
  print("\tundoes the last successful add,insert,remove or replace operation")
  print("help")
  print("\tdisplays help prompt")
  print("exit")
  print("\tcloses the application")


def print_contestant(contestant):
  print("scores: ",end="")
  for i in range(0,3):
    print(Contestant.get_score(contestant,i),end=" ")
  print("average score: %f" % (Contestant.get_score(contestant,None) / 3))

def print_contestants(contestants):
  for contestant in contestants:
    print_contestant(contestant)

