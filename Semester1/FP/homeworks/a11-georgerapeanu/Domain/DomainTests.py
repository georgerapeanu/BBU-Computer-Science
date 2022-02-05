import unittest

from Domain.Battleship import Battleship
from Domain.BattleshipMask import BattleshipMask
from Domain.BattleshipOrientation import BattleshipOrientation
from Domain.DomainExceptions import IdValidatorException, BattleshipException, MoveException
from Domain.GameData import GameData
from Domain.Move import Move
from Domain.MoveStatus import MoveStatus
from Domain.PlayerData import PlayerData


class BattleshipTests(unittest.TestCase):
    def setUp(self):
        self.battleship = Battleship(1, 2, False, 4, 5, BattleshipOrientation.VERTICAL, True)

    def test_getters(self):
        self.assertEqual(self.battleship.id, 1)
        self.assertEqual(self.battleship.size, 2)
        self.assertEqual(self.battleship.destroyed, False)
        self.assertEqual(self.battleship.x, 4)
        self.assertEqual(self.battleship.y, 5)
        self.assertEqual(self.battleship.orientation, BattleshipOrientation.VERTICAL)
        self.assertEqual(self.battleship.placed, True)

    def test_setters(self):
        self.battleship.size = 3
        self.battleship.destroyed = True
        self.battleship.x = 5
        self.battleship.y = 6
        self.battleship.orientation = BattleshipOrientation.HORIZONTAL
        self.battleship.placed = False
        self.assertEqual(self.battleship.id, 1)
        self.assertEqual(self.battleship.size, 3)
        self.assertEqual(self.battleship.destroyed, True)
        self.assertEqual(self.battleship.x, 5)
        self.assertEqual(self.battleship.y, 6)
        self.assertEqual(self.battleship.orientation, BattleshipOrientation.HORIZONTAL)
        self.assertEqual(self.battleship.placed, False)

    def test_raises_id(self):
        with self.assertRaises(Exception):
            self.battleship.id = 2
        with self.assertRaises(BattleshipException):
            boat = Battleship("", 2, False, 4, 5, BattleshipOrientation.VERTICAL, True)
        with self.assertRaises(BattleshipException):
            boat = Battleship(-2, 2, False, 4, 5, BattleshipOrientation.VERTICAL, True)

    def test_raises_size(self):
        with self.assertRaises(BattleshipException):
            boat = Battleship(0, "", False, 4, 5, BattleshipOrientation.VERTICAL, True)
        with self.assertRaises(BattleshipException):
            self.battleship.size = -2

    def test_raises_destroyed(self):
        with self.assertRaises(BattleshipException):
            self.battleship.destroyed = ""

    def test_raises_x(self):
        with self.assertRaises(BattleshipException):
            self.battleship.x = ""

    def test_raises_y(self):
        with self.assertRaises(BattleshipException):
            self.battleship.y = ""

    def test_raises_orientation(self):
        with self.assertRaises(BattleshipException):
            self.battleship.orientation = False

    def test_raises_placed(self):
        with self.assertRaises(BattleshipException):
            self.battleship.placed = ""

    def test_bounding_box(self):
        self.assertEqual(self.battleship.get_bounding_box(), [4, 5, 5, 5])
        self.battleship.orientation = BattleshipOrientation.HORIZONTAL
        self.assertEqual(self.battleship.get_bounding_box(), [4, 5, 4, 6])

    def test_eq(self):
        tmp_battleship = Battleship(
            self.battleship.id,
            self.battleship.size,
            self.battleship.destroyed,
            self.battleship.x,
            self.battleship.y,
            self.battleship.orientation,
            self.battleship.placed
        )
        self.assertEqual(self.battleship, tmp_battleship)
        tmp_battleship_mask = BattleshipMask(
            self.battleship.id,
            self.battleship.size,
            self.battleship.destroyed,
        )
        tmp_battleship_mask2 = BattleshipMask(
            self.battleship.id,
            self.battleship.size,
            self.battleship.destroyed,
        )
        self.assertEqual(tmp_battleship_mask2, tmp_battleship_mask)


class MoveTests(unittest.TestCase):
    def setUp(self):
        self.move = Move(0, 1, 2, 3, MoveStatus.PENDING)

    def test_getters(self):
        self.assertEqual(self.move.id, 0)
        self.assertEqual(self.move.player, 1)
        self.assertEqual(self.move.x, 2)
        self.assertEqual(self.move.y, 3)
        self.assertEqual(self.move.status, MoveStatus.PENDING)

    def test_setters(self):
        self.move.player = 2
        self.move.x = 3
        self.move.y = 4
        self.move.status = MoveStatus.HIT
        self.assertEqual(self.move.id, 0)
        self.assertEqual(self.move.player, 2)
        self.assertEqual(self.move.x, 3)
        self.assertEqual(self.move.y, 4)
        self.assertEqual(self.move.status, MoveStatus.HIT)

    def test_raises_id(self):
        with self.assertRaises(Exception):
            self.move.id = 2
        with self.assertRaises(MoveException):
            move = Move("", 1, 2, 3, MoveStatus.PENDING)
        with self.assertRaises(MoveException):
            move = Move(-2, 1, 2, 3, MoveStatus.PENDING)

    def test_raises_player(self):
        with self.assertRaises(MoveException):
            move = Move(2, "", 2, 3, MoveStatus.PENDING)

    def test_raises_x(self):
        with self.assertRaises(MoveException):
            self.move.x = ""

    def test_raises_y(self):
        with self.assertRaises(MoveException):
            move = Move(2, 1, 2, "", MoveStatus.PENDING)

    def test_raises_status(self):
        with self.assertRaises(MoveException):
            self.move.status = 0

    def test_eq(self):
        tmp_move = Move(
            self.move.id,
            self.move.player,
            self.move.x,
            self.move.y,
            self.move.status
        )
        self.assertEqual(self.move, tmp_move)


class GameDataTests(unittest.TestCase):
    def test_game_data(self):
        game_data = GameData(10, [])


class PlayerDataTests(unittest.TestCase):
    def test_player_data(self):
        player_data = PlayerData(1, 2, 3, 4)
