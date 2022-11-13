#!/usr/bin/swipl
% For a list a1...an with integer and distinct numbers, define apredicate to determine all subsets with sum of elements divisible with n.

% len(L:list, R:int)
% (i, i), (i, o)
len([], 0):-!.
len([_|T], R):-
  len(T, RT),
  R is RT + 1,
  !.

% subset(L:list, R:list)
% (i, i), (i, o)
subset([], []).
subset([H | T], [H | R]):-
  subset(T, R).
subset([_ | T], R):-
  subset(T, R).

% check(L:list, N:int)
% (i, i, i)
check([], C,  N):-
  C mod N =:= 0,
  !.
check([H | T], C, N):-
  CT is C + H,
  check(T, CT, N).

% generateAnswers(L:list)
% (i)
generateAnswers(L, R):-
  len(L, N),
  !,
  subset(L, R),
  check(R, 0, N).

testLen:-
  len([], 0),
  len([1], 1),
  len([1,1,2], 3).

testSubset:-
  subset([], []),
  subset([1,2,3], [1,3]).

testCheck:-
  check([], 0, 1),
  \+ check([2,3], 0, 2),
  check([2,3], 0, 5).

testAll:-
  testLen,
  testSubset,
  testCheck.

