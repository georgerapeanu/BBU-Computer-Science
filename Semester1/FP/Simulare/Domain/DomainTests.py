import unittest

from Domain.Exceptions import MoveException
from Domain.Move import Move


class MoveTests(unittest.TestCase):
    def test_init(self):
        move = Move(1, 0, 0, 'X')
        with self.assertRaises(Exception):
            move = Move(-1, 0, 0, 'X')

        with self.assertRaises(Exception):
            move = Move("-1", 0, 0, 'X')

        with self.assertRaises(MoveException):
            move = Move(0, '0', 0, 'X')

        with self.assertRaises(MoveException):
            move = Move(0, 0, '0', 'X')

        with self.assertRaises(MoveException):
            move = Move(0, 0, '0', 'XX')

        with self.assertRaises(MoveException):
            move = Move(0, 0, '0', '')
        move = Move(0, 0, 0, 'O')

    def test_equ(self):
        move = Move(1, 0, 0, 'X')
        move2 = Move(1, 0, 1, 'O')
        self.assertNotEqual(move, move2)
        move2.value = 'X'
        self.assertNotEqual(move, move2)
        move.y = 1
        self.assertEqual(move, move2)

    def test_setters(self):
        move = Move(1, 0, 0, 'X')
        with self.assertRaises(Exception):
            move.id = 2

        with self.assertRaises(MoveException):
            move.x = ""
        move.x = 5
        self.assertEqual(move.x, 5)

        with self.assertRaises(MoveException):
            move.y = ""
        move.y = -2
        self.assertEqual(move.y, -2)

        move.value = 'O'
        with self.assertRaises(MoveException):
            move.value = 'U'

        with self.assertRaises(MoveException):
            move.value = 1

    def test_getters(self):
        move = Move(1, 2, 3, 'X')
        self.assertEqual(move.id, 1)
        self.assertEqual(move.x, 2)
        self.assertEqual(move.y, 3)
        self.assertEqual(move.value, 'X')

    def test_str(self):
        move = Move(1, 2, 3, 'X')
        self.assertEqual(str(move), "Move #1 2 3 X")

    def test_init_from_string(self):
        with self.assertRaises(MoveException):
            move = Move.init_from_string(1)
        with self.assertRaises(MoveException):
            move = Move.init_from_string("12312")
        with self.assertRaises(MoveException):
            move = Move.init_from_string("Move #2 3 3 U")
        move = Move.init_from_string("Move #1 2 3 X")
        self.assertEqual(move, Move(1, 2, 3, 'X'))
