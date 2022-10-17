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
% Usage: removeFirstNOccurences(element, N, input_list, output_list).

removeFirstNOccurences(_, _, [], []).
removeFirstNOccurences(_, 0, L, L).
removeFirstNOccurences(K, N, [H|T], R):-
  N > 0,
  K =:= H,
  NT is N - 1,
  removeFirstNOccurences(K, NT, T, R).

removeFirstNOccurences(K, N, [H|T], R):-
  N > 0,
  K =\= H,
  removeFirstNOccurences(K, N, T, RT),
  R=[H|RT].

% Usage: removeFirst3Occuranges(element, input_list, output_list).
removeFirst3Occurences(K, L, R):- removeFirstNOccurences(K, 3, L, R).


% Tests begin here

?- \+ checkElementInList(1, []).
?- checkElementInList(1, [1]).
?- checkElementInList(1, [1, 2]).
?- \+ checkElementInList(1, [2]).
?- \+ checkElementInList(4, [1, 5, 2, 3]).
?- checkElementInList(4, [1, 5, 4, 3, 4]).

?- checkIfListIsSet([]).
?- checkIfListIsSet([1]).
?- \+ checkIfListIsSet([1, 1]).
?- \+ checkIfListIsSet([1, 2, 3, 4, 4, 3]).
?- checkIfListIsSet([1, 2, 4, 3]).

?- removeFirstNOccurences(1, 0, [4], [4]).
?- removeFirstNOccurences(1, 1, [4], [4]).
?- removeFirstNOccurences(1, 1, [1, 4], [4]).
?- removeFirstNOccurences(1, 4, [1, 4], [4]).
?- removeFirstNOccurences(0, 10, [], []).
?- removeFirstNOccurences(3, 4, [1, 4, 3, 2, 3, 3, 3, 3], [1, 4, 2, 3]).

?- removeFirst3Occurences(3, [1, 4, 3, 2, 3, 3, 3, 3], [1, 4, 2, 3, 3]).
?- removeFirst3Occurences(3, [1, 4, 3, 3, 3], [1, 4]).
?- removeFirst3Occurences(3, [1, 4, 3, 3], [1, 4]).
?- removeFirst3Occurences(1, [1, 4, 3, 3], [4, 3, 3]).
?- removeFirst3Occurences(1, [], []).

