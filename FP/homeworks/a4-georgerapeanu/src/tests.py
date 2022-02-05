#!/usr/bin/python3

#@author: Rapeanu George

import tests_Contestant
import tests_Functions
import tests_start

def run_tests():
  tests_Contestant.run_tests()
  tests_Functions.run_tests()
  tests_start.run_tests()

if __name__ == "__main__":
  run_tests()
