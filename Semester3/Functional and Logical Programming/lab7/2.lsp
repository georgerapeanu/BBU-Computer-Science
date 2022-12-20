#!/usr/bin/clisp

; 2.Write a function that returns the sum of numeric atoms in a list, atany level.

; Usage: calculateSum(l:list|number|atom) -> returns integer
(defun calculateSum(l)
  (cond 
    ((null l) 0)
    ((numberp l) l)
    ((atom l) 0)
    (t (apply #'+ (mapcar #'calculateSum l)))
  )
)

; Usage calculateSumAtDepthRange(l:list|number|atom, low:number, high:number)
; precondition low <= high
(defun calculateSumAtDepthRange(l low high)
  (cond
    ((null l) 0)
    ((< high 0) 0) ; high >= 0 in the other cases
    ((numberp l) (cond ((<= low 0) l) (t 0)))
    ((atom l) 0)
    (t (apply #'+ (mapcar (lambda (x) (calculateSumAtDepthRange x (- low 1) (- high 1))) l)))
  )
)

(defun testCalculateSum()
  (assert (equal (calculateSum '()) 0))
  (assert (equal (calculateSum '(1 2 3 4 5 a s)) 15))
  (assert (equal (calculateSum '((1 2 3) ((4) (5)) (a) s)) 15))
)

(defun testCalculateSumAtDepthRange()
  (assert (equal (calculateSumAtDepthRange '() 0 100) 0))
  (assert (equal (calculateSumAtDepthRange '(1 2 3 4 5 a s) 1 1 ) 15))
  (assert (equal (calculateSumAtDepthRange '(1 2 3 4 5 a s) 2 2 ) 0))
  (assert (equal (calculateSumAtDepthRange '((1 2 3) ((4) (5)) (a) s) 1 1) 0))
  (assert (equal (calculateSumAtDepthRange '((1 2 3) ((4) (5)) (a) s) 2 2) 6))
  (assert (equal (calculateSumAtDepthRange '((1 2 3) ((4) (5)) (a) s) 3 3) 9))
  (assert (equal (calculateSumAtDepthRange '((1 2 3) ((4) (5)) (a) s) 1 3) 15))
)

(defun testAll() 
  (testCalculateSum)
  (testCalculateSumAtDepthRange)
)
