#!/usr/bin/swipl

% write a predicate to replace a given element from a list, with another list
% [1 2 3 1] 1 [11 22 33] -> [11 22 33 2 3 11 22 33]
% [2 3 4] 1 [11 22 33] -> [2 3 4]


% flow model (i, i, o), (i, i, i)
% Usage concat(A:list, B:list, R:list)
% concatantes 2 given lists
concat([], A, A):-!.

concat([H | T], A, [H | RT]):-
  concat(T, A, RT).

% flow model (i, i, i, o), (i, i, i, i)
% Usage replaceElementWithList(L:list, E: element, A: list, R: list)
% replaces each occurence of element E in L with the elements of A
replaceElementWithList([], _, _, []):-!.

replaceElementWithList([H | T], H, A, R):-
  replaceElementWithList(T, H, A, RT),
  concat(A, RT, R).

replaceElementWithList([H | T], E, A, [H | RT]):-
  H =\= E,
  !,
  replaceElementWithList(T, E, A, RT).

testConcat:-
  concat([], [], []),
  concat([], [1,2,3], [1,2,3]),
  concat([1], [1,2,3], [1, 1,2,3]),
  concat([2,4,3], [1,2,3], [2,4,3,1,2,3]),
  concat([2], [], [2]).

testReplaceElementWithList:-
  replaceElementWithList([1,2,3,1], 1, [11,22,33], [11,22,33,2,3,11,22,33]),
  replaceElementWithList([2,3,4], 1, [11,22,33], [2,3,4]),
  replaceElementWithList([1,2,3,4,2,1,6,7,1,8], 1, [11,22,33], [11,22,33,2,3,4,2,11,22,33,6,7,11,22,33,8]),
  replaceElementWithList([1,2,3,4],1,[11,22,33], [11,22,33,2,3,4]).

testAll:-
  testConcat,
  testReplaceElementWithList.
  
