#!/usr/bin/python3

def pw(n, e):
  if e == 0:
    return 1
  if e % 2 == 1:
    return n * pw(n * n, e // 2)
  return pw(n * n, e // 2)

print(pw(2, 10))
