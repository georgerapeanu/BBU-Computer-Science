#!/usr/bin/python3

#@author: Rapeanu George

from test_utils import *
from Contestant import *
from Functions import *

def test_insert_contestant():
  history = []
  contestants = [create_contestant([1,0,0]),create_contestant([2,1,4])]
  
  assert(has_exception(insert_contestant,(history,contestants,create_contestant([0,0,0]),-1)) == True)
  
  assert(has_exception(insert_contestant,(history,contestants,create_contestant([0,0,0]),3)) == True)

  insert_contestant(history,contestants,create_contestant([0,0,0]))
  assert(contestants == [create_contestant([1,0,0]),create_contestant([2,1,4]),create_contestant([0,0,0])])
  insert_contestant(history,contestants,create_contestant([1,1,1]),2)
  assert(contestants == [create_contestant([1,0,0]),create_contestant([2,1,4]),create_contestant([1,1,1]),create_contestant([0,0,0])])
  undo(history,contestants)
  assert(contestants == [create_contestant([1,0,0]),create_contestant([2,1,4]),create_contestant([0,0,0])])

def test_remove_contestants():
  history = []
  contestants = [create_contestant([1,0,0]),
                 create_contestant([2,1,4]),
                 create_contestant([3,1,4]),
                 create_contestant([4,10,4]),
                ]
  
  assert(has_exception(remove_range_contestants,(history,contestants,-1,2)) == True)
  assert(has_exception(remove_range_contestants,(history,contestants,0,10)) == True)
  assert(has_exception(remove_range_contestants,(history,contestants,3,2)) == True)


  remove_range_contestants(history,contestants,1,2)
  assert(contestants == [create_contestant([1,0,0]),create_contestant([4,10,4])])
  remove_filter_contestants(history,contestants,(lambda x: get_score(x,0) == 1))
  assert(contestants == [create_contestant([4,10,4])])
  undo(history,contestants)
  assert(contestants == [create_contestant([1,0,0]),create_contestant([4,10,4])])

def test_replace_contestant():
  history = []
  contestants = [create_contestant([10,0,0]),
                 create_contestant([2,10,4]),
                 create_contestant([3,10,4]),
                 create_contestant([4,10,4]),
                ]
  
  assert(has_exception(replace_contestant, (history,contestants,-1,0,0)) == True)
  assert(has_exception(replace_contestant, (history,contestants,100,10,10)) == True)
  replace_contestant(history,contestants,0,1,10)
  assert (contestants == [create_contestant([10,10,0]),
                          create_contestant([2,10,4]),
                          create_contestant([3,10,4]),
                          create_contestant([4,10,4])])
  undo(history,contestants)
  assert (contestants == [create_contestant([10,0,0]),
                          create_contestant([2,10,4]),
                          create_contestant([3,10,4]),
                          create_contestant([4,10,4])])

def test_list_contestants():
  contestants = [create_contestant([1,0,0]),
                 create_contestant([2,10,4]),
                 create_contestant([3,10,4]),
                 create_contestant([4,10,4]),
                ]
  assert(list_contestants(contestants,None,None) == \
                [create_contestant([1,0,0]),
                 create_contestant([2,10,4]),
                 create_contestant([3,10,4]),
                 create_contestant([4,10,4]),
                ])
  
  assert(list_contestants(contestants,lambda x: -get_score(x,None),None) == \
                [
                 create_contestant([4,10,4]),
                 create_contestant([3,10,4]),
                 create_contestant([2,10,4]),
                 create_contestant([1,0,0]),
                ])
  
  assert(list_contestants(contestants,None,lambda x: get_score(x,None) > 15) == \
                [
                 create_contestant([2,10,4]),
                 create_contestant([3,10,4]),
                 create_contestant([4,10,4]),
                ])
  assert(list_contestants(contestants,lambda x: -get_score(x,None),lambda x: get_score(x,None) > 15) == \
                [
                 create_contestant([4,10,4]),
                 create_contestant([3,10,4]),
                 create_contestant([2,10,4]),
                ])

def test_calculate_function():
  contestants = [create_contestant([1,0,0]),
                 create_contestant([2,10,4]),
                 create_contestant([3,10,4]),
                 create_contestant([4,10,4])]
  extractor = (lambda x: get_score(x,None) / 3)
  avg = (lambda x:sum(x) / len(x))
  
  assert(has_exception(calculate_function,(contestants,extractor,avg,-1,2)))
  assert(has_exception(calculate_function,(contestants,extractor,avg,2,100)))
  assert(abs(calculate_function(contestants,extractor,avg,2,3) - 35 / 6) < 1e-5)
  assert(abs(calculate_function(contestants,extractor,min,0,2) - 1 / 3) < 1e-5)

def test_top_contestants():
  contestants = [create_contestant([1,0,0]),
                 create_contestant([2,10,4]),
                 create_contestant([3,10,4]),
                 create_contestant([4,10,4])]
  assert(has_exception(top_contestants,(10,lambda x:0)))
  assert(has_exception(top_contestants,(-1,lambda x:0)))
  assert(top_contestants(contestants,2,lambda x:-get_score(x,None)) == [create_contestant([4,10,4]),create_contestant([3,10,4])])
  assert(top_contestants(contestants,2,lambda x:get_score(x,0)) == [create_contestant([1,0,0]),
                                                                    create_contestant([2,10,4])])

def run_tests():
  test_insert_contestant()
  test_remove_contestants()
  test_replace_contestant()
  test_list_contestants()
  test_calculate_function()
  test_top_contestants()

