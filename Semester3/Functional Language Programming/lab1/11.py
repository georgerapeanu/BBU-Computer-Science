#!/usr/bin/python3
# 11. a. Determine if a certain element is member in a list.
#     b. Determine the length of a list.

class Node:
  def __init__(self, elem, nextNode):
      self.elem = elem
      self.nextNode = nextNode

def addToList(head, elem):
  """ Adds element `elem` before the node `head`.
      @param head: the head of the list
      @type head: Node
      @param elem: the element to be added
      @returns: The head of the list after the add
  """
  node = Node(elem, head)
  return node

def determineIfElementExists(head, elem):
  """ Checks if a given elemenet `elem` is in the list which starts at with the node `head`
      @param head: the head of the list
      @type head: Node
      @param elem: the element to be searched
      @returns: True if element exists in list, False otherwise
  """
  if head is None:
    return False

  if elem == head.elem:
    return True

  return determineIfElementExists(head.nextNode, elem)

def determineListLength(head):
  """ Determines the length of the list which starts with the node `head`
      @param head: the head of the list
      @type head: Node
      @returns: an integer representing the length of the list
  """
  if head is None:
    return 0

  return 1 + determineListLength(head.nextNode)

def testDetermineIfElementExists():
  head = None
  assert(determineIfElementExists(head, 2) == False)
  head = addToList(head, 3)
  assert(determineIfElementExists(head, 2) == False)
  head = addToList(head, 2)
  assert(determineIfElementExists(head, 2) == True)
  head = addToList(head, 3)
  assert(determineIfElementExists(head, 2) == True)
  assert(determineIfElementExists(head, 3) == True)
  assert(determineIfElementExists(head, 4) == False)


def testDetermineListLength():
  head = None
  assert(determineListLength(head) == 0)
  head = addToList(head, 3)
  assert(determineListLength(head) == 1)
  head = addToList(head, 2)
  assert(determineListLength(head) == 2)
  head = addToList(head, 3)
  assert(determineListLength(head) == 3)

def testAll():
  testDetermineIfElementExists()
  testDetermineListLength()

if __name__ == '__main__':
  testAll()

