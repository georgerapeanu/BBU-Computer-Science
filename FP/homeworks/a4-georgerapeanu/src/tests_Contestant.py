#!/usr/bin/python3

#@author: Rapeanu George

from Contestant import *

def test_get_score():
  contestant = create_contestant([10,5,4])
  assert(get_score(contestant,0) == 10)
  assert(get_score(contestant,1) == 5)
  assert(get_score(contestant,2) == 4)
  assert(get_score(contestant,None) == 19)

def test_set_score():
  contestant = create_contestant([10,5,4])
  set_score(contestant,0,2)
  assert(get_score(contestant,0) == 2)
  assert(get_score(contestant,1) == 5)
  assert(get_score(contestant,2) == 4)
  assert(get_score(contestant,None) == 11)

def run_tests():
  test_get_score()
  test_set_score()
