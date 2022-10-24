#!/usr/bin/swipl -q

% 1.   
% a. Sort a list with removing the double values. E.g.: [4 2 6 2 3 4] --> [2 3 4 6]
% b. For a heterogeneous list, formed from integer numbers and list of numbers, write a predicate to sort every sublist with removing the doubles.Eg.: [1, 2, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] =>[1, 2, [1, 4], 3, 6, [1, 3, 7, 9, 10], 5, [1], 7].

% Usage: countOccurences(list, Element, Answer) - returns in Answer the number of times Element Element occurs in list

countOccurences([], _, 0):-!.

countOccurences([H | T], Element, Answer):-
  H =:= Element,
  !,
  countOccurences(T, Element, AnswerT),
  !,
  Answer is AnswerT + 1.

countOccurences([H | T], Element, Answer):-
  H =\= Element,
  !,
  countOccurences(T, Element, Answer),
  !.

% Usage: getMin(list, Answer) - returns in Answer the minimum from the list

getMin([E], E):-!.

getMin([H | T], Answer):-
  getMin(T, AnswerT),
  H < AnswerT,
  Answer is H,
  !.

getMin([H | T], Answer):-
  getMin(T, AnswerT),
  H >= AnswerT,
  Answer is AnswerT,
  !.

% Usage: removeElementFromList(list, Element, Answer) - returns in Answer the list after Element has been removed from it.
% In case element doesn't exist in list, it returns the list unaffected.

removeElementFromList([], _, []).

removeElementFromList([H | T], H, T):-!.

removeElementFromList([H | T], Element, [H | AnswerT]):-
  H =\= Element,
  !,
  removeElementFromList(T, Element, AnswerT),
  !.

% Usage: sortAndUnique(list, Answer) - returns in Answer the sorted list , with no duplicates

sortAndUnique([], []).

sortAndUnique(L, Answer):-
  getMin(L, Minimum),
  removeElementFromList(L, Minimum, AnswerL),


testCountOccurences:- 
  countOccurences([], 1, 0),
  countOccurences([1,2,3,4],0,0),
  countOccurences([1,2,3,4],2,1),
  countOccurences([1,2,3,4,2,2,2,2],2,5).

testGetMin:-
  getMin([1,4,2,3,4,2], 1),
  getMin([4,6,2,4], 2).

testRemoveElementFromList:-
  removeElementFromList([], 232, []),
  removeElementFromList([1,2,3], 232, [1,2,3]),
  removeElementFromList([1,2], 2, [1]),
  removeElementFromList([1,2], 1, [2]).

testAll:-
  testCountOccurences,
  testGetMin,
  testRemoveElementFromList.
