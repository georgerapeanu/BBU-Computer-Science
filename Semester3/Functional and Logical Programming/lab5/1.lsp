#!/usr/bin/clisp

; 1.
; a) Write a function to return the n-th element of a list, or NIL if such an element does not exist.
;b) Write a function to check whether an atom E is a member of a list which is not necessarily linear.
;c) Write a function to determine the list of all sublists of a given list, on any level.
;A sublist is either the list itself, or any element that is a list, at any level. Example:
;(1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 sublists :
;( (1 2 (3 (4 5) (6 7)) 8 (9 10)) (3 (4 5) (6 7)) (4 5) (6 7) (9 10) )
;d) Write a function to transform a linear list into a set

; flow model (i i)
; getNthElement(l: list n: int) -> atom
(defun getNthElement(l n)
  (cond 
    ((null l) nil)
    ((< n 1) nil)
    ((equal n 1) (car l))
    (t (getNthElement (cdr l) (- n 1)))
  )
)

; flow model (i i)
; checkIfAtomIsInList(l: list e: atom) -> t/nil
(defun checkIfAtomIsInList(l e)
  (cond
    ((null l) nil)
    ((and (atom (car l)) (equal e (car l))) t)
    ((atom (car l)) (checkIfAtomIsInList (cdr l) e))
    ((list (car l)) (or (checkIfAtomIsInList (car l) e) (checkIfAtomIsInList (cdr l) e)))
    (t nil)
  )
)

; flow model (i i)
; getAllIncludedSublists(l: list current: list) -> list
(defun getAllIncludedSublists(l current)
  (cond
    ((null l) current)
    ((atom (car l)) (getAllIncludedSublists (cdr l) current))
    (t (getAllIncludedSublists (cdr l) (concatenate 'list current (cons (car l) nil) (getAllIncludedSublists (car l) '()))))
  )
)

; flow model (i)
; getAllSublists(l: list) -> list
(defun getAllSublists(l)
  (concatenate 'list (cons l nil) (getAllIncludedSublists l '()))
)

; flow model (i i)
; appears(l:list e:atom) -> t/nil
(defun appears(l e)
  (cond
   ((null l) nil)
   ((= (car l) e) t)
   (t (appears (cdr l) e))
  )
)

; flow model (i)
; listToSet(l:list) -> set
(defun listToSet(l)
  (cond
    ((null l) '())
    ((appears (cdr l) (car l)) (listToSet (cdr l)))
    (t (concatenate 'list (cons (car l) nil) (listToSet (cdr l))))
  )
)

(defun testGetNthElement()
  (assert (equal (getNthElement '(1 2 5 4 3) 0) nil))
  (assert (equal (getNthElement '(1 2 5 4 3) 1) 1))
  (assert (equal (getNthElement '(1 2 5 4 3) 2) 2))
  (assert (equal (getNthElement '(1 2 5 4 3) 3) 5))
  (assert (equal (getNthElement '(1 2 5 4 3) 4) 4))
  (assert (equal (getNthElement '(1 2 5 4 3) 5) 3))
  (assert (equal (getNthElement '(1 2 5 4 3) 6) nil))
)

(defun testCheckIfAtomInList()
  (assert (not (checkIfAtomIsInList '() 1)))
  (assert (not (checkIfAtomIsInList '(2 4 3) 1)))
  (assert (not (checkIfAtomIsInList '(2 4 3 (5 6)) 1)))
  (assert (checkIfAtomIsInList '(2 4 3) 2))
  (assert (checkIfAtomIsInList '(2 4 3 (5 6)) 5))
)

(defun testGetAllIncludedSublists()
  (assert (equal (getAllIncludedSublists '() '()) '()))
  (assert (equal (getAllIncludedSublists '(1 2 3 4) '()) '()))
  (assert (equal (getAllIncludedSublists '(1 2 (5 6) 3 4 (7 (8 9))) '()) '((5 6) (7 (8 9)) (8 9))))
)

(defun testGetAllSublists()
  (assert (equal (getAllSublists '()) '(())))
  (assert (equal (getAllSublists '(1 2 3 4)) '((1 2 3 4))))
  (assert (equal (getAllSublists '(1 2 (5 6) 3 4 (7 (8 9)))) '((1 2 (5 6) 3 4 (7 (8 9))) (5 6) (7 (8 9)) (8 9))))
  (assert (equal (getAllSublists '(1 2 (3 (4 5) (6 7)) 8 (9 10))) '((1 2 (3 (4 5) (6 7)) 8 (9 10)) (3 (4 5) (6 7)) (4 5) (6 7) (9 10))))
)

(defun testAppears()
  (assert (not (appears '()  1)))
  (assert (not (appears '()  2)))
  (assert (not (appears '()  3)))
  (assert (not (appears '(4 5 6)  3)))
  (assert (appears '(4 5 6)  4))
  (assert (appears '(4 5 6)  5))
  (assert (appears '(4 5 6)  6))
)

(defun testListToSet()
  (assert (equal (listToSet '()) '()))  
  (assert (equal (listToSet '(1 2 3 4)) '(1 2 3 4)))  
  (assert (equal (listToSet '(2 2 2 4 4 4 3)) '(2 4 3)))
  (assert (equal (listToSet '(9 2 8 3 2)) '(9 8 3 2)))
)

(defun testAll()
  (testGetNthElement) 
  (testCheckIfAtomInList)
  (testGetAllIncludedSublists)
  (testGetAllSublists)
  (testAppears)
  (testListToSet)
)
