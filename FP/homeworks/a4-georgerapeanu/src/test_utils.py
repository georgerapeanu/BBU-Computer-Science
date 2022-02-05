#!/usr/bin/python3

#@author: Rapeanu George

def has_exception(function,args):
  try:
    function(*args)
  except Exception:
    return True
  return False

