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

(defun testCalculateSum()
  (assert (equal (calculateSum '()) 0))
  (assert (equal (calculateSum '(1 2 3 4 5 a s)) 15))
  (assert (equal (calculateSum '((1 2 3) ((4) (5)) (a) s)) 15))
)

(defun testAll() 
  (testCalculateSum)
)
