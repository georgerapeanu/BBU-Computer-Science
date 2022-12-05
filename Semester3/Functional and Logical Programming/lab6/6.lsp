#!/usr/bin/clisp

;write recursive Lisp functions for the following problems (optionally,you may use MAP functions):
; A binary tree is memorised in the following two ways:
;   (node no-subtrees list-subtree-1 list-subtree-2 ...) (1)
;   (node (list-subtree-1) (list-subtree-2) ...)         (2)
;6. Return the list of nodes of a tree of type (1) accessed inorder.

; flow model (i i)
; getNthElement(l: list n: int) -> atom
; 0 indexed
(defun getNthElement(l n)
  (cond 
    ((null l) nil)
    ((< n 1) nil)
    ((equal n 1) (car l))
    (t (getNthElement (cdr l) (- n 1)))
  )
)

; flow model (i)
; skipFirstTree(l:list) -> list from which the first tree is removed
(defun skipFirstTree(l)
  (cond
    ((null l) '())
    ((equal (getNthElement l 2) 0) (cdr (cdr l)))
    ((equal (getNthElement l 2) 1) (skipFirstTree (cdr (cdr l))))
    ((equal (getNthElement l 2) 2) (skipFirstTree (skipFirstTree (cdr (cdr l)))))
  )
)

; flow model (i)
; inorderWalk(l:list)
(defun inorderWalk(l)
  (cond
    ((null l) '())
    ((equal (getNthElement l 2) 0) (concatenate 'list (cons (getNthElement l 1) nil)))
    ((equal (getNthElement l 2) 1) (concatenate 'list (inorderWalk (cdr (cdr l))) (cons (getNthElemeht l 1) nil)))
    ((equal (getNthElement l 2) 2) (concatenate 'list (inorderWalk (cdr (cdr l))) (cons (getNthElement l 1) nil) (inorderWalk (skipFirstTree (cdr (cdr l))))))
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

(defun testSkipFirstTree()
  (assert (equal (skipFirstTree '()) '()))
  (assert (equal (skipFirstTree '(A 2 B 0 C 2 D 0 E 0)) '()))
  (assert (equal (skipFirstTree '(B 0 C 2 D 0 E 0)) '(C 2 D 0 E 0)))
  (assert (equal (skipFirstTree '(C 2 D 0 E 0)) '()))
  (assert (equal (skipFirstTree '(D 0 E 0)) '(E 0)))
  (assert (equal (skipFirstTree '(E 0)) '()))
)

(defun testInOrderWalk()
  (assert (equal (inOrderWalk '()) '()))
  (assert (equal (inOrderWalk '(A 2 B 0 C 2 D 0 E 0)) '(B A D C E)))
  (assert (equal (inOrderWalk '(B 0)) '(B)))
  (assert (equal (inOrderWalk '(C 2 D 0 E 0)) '(D C E)))
  (assert (equal (inOrderWalk '(D 0)) '(D)))
  (assert (equal (inOrderWalk '(E 0)) '(E)))
)

(defun testAll()
  (testGetNthElement)
  (testSkipFirstTree)
  (testInOrderWalk)
)
