#!/usr/bin/swipl -q

% 1.   
% a. Sort a list with removing the double values. E.g.: [4 2 6 2 3 4] --> [2 3 4 6]
% b. For a heterogeneous list, formed from integer numbers and list of numbers, write a predicate to sort every sublist with removing the doubles.Eg.: [1, 2, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] =>[1, 2, [1, 4], 3, 6, [1, 3, 7, 9, 10], 5, [1], 7].


% (i, i, o) (i, i, i)
% Usage: mergeUnique(A, B, Answer) -> merges the 2 sorted lists A and B and removes duplicates

mergeUnique(A, [], A):-!.
mergeUnique([], B, B):-!.

mergeUnique([HA | TA], [HB | TB], [HA | AnswerT]):-
  HA < HB,
  !,
  mergeUnique(TA, [HB | TB], AnswerT).

mergeUnique([HA | TA], [HB | TB], [HB | AnswerT]):-
  HB < HA,
  !,
  mergeUnique([HA | TA], TB, AnswerT).

mergeUnique([H | TA], [H | TB], [H | AnswerT]):-
  !,
  mergeUnique(TA, TB, AnswerT).


% Usage: splitEqually(L, A, B) -> splits the elements of L almost equally in A and B
splitEqually([], [], []):- !.
splitEqually([H | T], [H | AnswerA], AnswerB):-
  splitEqually(T, AnswerB, AnswerA).

% Usage: mergeSortUnique(A, Answer) -> sorts and uniques
mergeSortUnique(A, A):- 
  length(A, LenA), 
  LenA =< 1, 
  !.
%(i, o), (i, i)
mergeSortUnique(A, Answer):-
  length(A, LenA),
  LenA > 1,
  !,
  splitEqually(A, LA, RA),
  mergeSortUnique(LA, LA_SORTED),
  mergeSortUnique(RA, RA_SORTED),
  mergeUnique(LA_SORTED, RA_SORTED, Answer).
% (i, o)
%Usage: solveHeterogenousList(A, Answer) -> sorts all sublists of A
solveHeterogenousList([], []).

solveHeterogenousList([H | T], [AnswerH | AnswerT]):-
  is_list(H),
  !,
  mergeSortUnique(H, AnswerH),
  solveHeterogenousList(T, AnswerT).

solveHeterogenousList([H | T], [H | AnswerT]):-
  \+ is_list(H),
  !,
  solveHeterogenousList(T, AnswerT).

% modification
mergeUniqueDesc(A, [], A):-!.
mergeUniqueDesc([], B, B):-!.

mergeUniqueDesc([HA | TA], [HB | TB], [HA | AnswerT]):-
  HA > HB,
  !,
  mergeUniqueDesc(TA, [HB | TB], AnswerT).

mergeUniqueDesc([HA | TA], [HB | TB], [HB | AnswerT]):-
  HB > HA,
  !,
  mergeUniqueDesc([HA | TA], TB, AnswerT).

mergeUniqueDesc([H | TA], [H | TB], [H | AnswerT]):-
  !,
  mergeUniqueDesc(TA, TB, AnswerT).

mergeSortUniqueDesc(A, A):- 
  length(A, LenA), 
  LenA =< 1, 
  !.

mergeSortUniqueDesc(A, Answer):-
  length(A, LenA),
  LenA > 1,
  !,
  splitEqually(A, LA, RA),
  mergeSortUniqueDesc(LA, LA_SORTED),
  mergeSortUniqueDesc(RA, RA_SORTED),
  mergeUniqueDesc(LA_SORTED, RA_SORTED, Answer).

mergeSortUniqueComp(A, Increasing, Answer):-
  Increasing,
  !,
  mergeSortUnique(A, Answer). 

mergeSortUniqueComp(A, Increasing, Answer):-
  \+ Increasing,
  !,
  mergeSortUniqueDesc(A, Answer). 

testMergeUnique:-
  mergeUnique([], [], []),
  mergeUnique([1,2,3,4], [], [1,2,3,4]),
  mergeUnique([], [1,2,3,4], [1,2,3,4]),
  mergeUnique([1,2,4], [3,5], [1,2,3,4,5]),
  mergeUnique([1,2,4,5,6], [1,2,3,5], [1,2,3,4,5,6]).

testSplitEqually:-
  splitEqually([], [], []),
  splitEqually([1,2,3,4], [1,3], [2,4]),
  splitEqually([1, 2, 3], [1, 3], [2]),
  splitEqually([1, 1, 1, 1], [1, 1], [1, 1]),
  splitEqually([4], [4], []).

testMergeSortUnique:-
  mergeSortUnique([], []),
  mergeSortUnique([4,2,3,21,4,5], [2,3,4,5,21]),
  mergeSortUnique([1,1,1,1,1,1], [1]), 
  mergeSortUnique([1], [1]), 
  mergeSortUnique([0,0,0,0,0,0,1,1,1,1,11,2,2,2,2,2,23,3,3,3,3,4,4,4,4,4], [0,1,2,3,4,11,23]).

testMergeSortUniqueComp:-
  mergeSortUniqueComp([], true, []),
  mergeSortUniqueComp([4,2,3,21,4,5], true, [2,3,4,5,21]),
  mergeSortUniqueComp([1,1,1,1,1,1], true, [1]), 
  mergeSortUniqueComp([1], true, [1]), 
  mergeSortUniqueComp([0,0,0,0,0,0,1,1,1,1,11,2,2,2,2,2,23,3,3,3,3,4,4,4,4,4], true, [0,1,2,3,4,11,23]),
  mergeSortUniqueComp([], false, []),
  mergeSortUniqueComp([4,2,3,21,4,5], false, [21,5,4,3,2]),
  mergeSortUniqueComp([1,1,1,1,1,1], false, [1]), 
  mergeSortUniqueComp([1], false, [1]), 
  mergeSortUniqueComp([0,0,0,0,0,0,1,1,1,1,11,2,2,2,2,2,23,3,3,3,3,4,4,4,4,4], false, [23,11,4,3,2,1,0]).

testSolveHeterogenousList:-
  solveHeterogenousList([], []),
  solveHeterogenousList([1,4,2,3], [1,4,2,3]),
  solveHeterogenousList([1,1,1,1,[2,3,4,5,1]], [1,1,1,1,[1,2,3,4,5]]).

testAll:-
  testMergeUnique,
  testSplitEqually,
  testMergeSortUnique,
  testMergeSortUniqueComp,
  testSolveHeterogenousList.
