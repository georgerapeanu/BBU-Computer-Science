from Contestant import *
from Functions import *
from start import *

def test_parse_command():
  assert(parse_command(" add 10 2  1  ") == (insert_contestant,(create_contestant([10,2,1]),None))) 
  assert(parse_command(" insert  10 2  1  at 2") == (insert_contestant,(create_contestant([10,2,1]),2))) 
  assert(parse_command("remove  10") == (remove_range_contestants,(10,10))) 
  assert(parse_command("remove  10 to 12") == (remove_range_contestants,(10,12))) 
  assert(parse_command("replace  10 P2 with 2") == (replace_contestant,(10,1,2))) 
  assert(parse_command("list") == (list_contestants,(None,None)))

def run_tests():
  test_parse_command()
