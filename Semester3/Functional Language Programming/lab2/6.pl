#!/usr/bin/swipl -q 

% 6.
% a. Write a predicate to test if a list is a set.
% b. Write a predicate to remove the first three occurrences of an element in a list. If the element occurs less than three times, all occurrences will be removed.

% a
% Usage: checkElementInList(element, list).

checkElementInList(_, []):- false.

checkElementInList(K, [H|_]):-
  K =:= H.

checkElementInList(K, [_|T]):-
  checkElementInList(K, T).

checkIfListIsSet([]):- true.

% Usage: checkIfListIsSet(list).
checkIfListIsSet([H|T]):-
  not(checkElementInList(H, T)),
  checkIfListIsSet(T).

% b
% Usage: removeFirstNOccurances(element, N, input_list, output_list).

removeFirstNOccurances(_, _, [], []).
removeFirstNOccurances(_, 0, L, L).
removeFirstNOccurances(K, N, [H|T], R):-
  N > 0,
  K =:= H,
  NT is N - 1,
  removeFirstNOccurances(K, NT, T, R).

removeFirstNOccurances(K, N, [H|T], R):-
  N > 0,
  K =\= H,
  removeFirstNOccurances(K, N, T, RT),
  R=[H|RT].
