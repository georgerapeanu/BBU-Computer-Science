import unittest

from Domain.Exceptions import AppException
from Domain.Move import Move
from Repository.GeneralFileRepository import GeneralFileRepository
from Service.AI import AI
from Service.GameController import GameController
from Service.GameUtils import GameUtils


class GameUtilsTests(unittest.TestCase):

    def setUp(self):
        self.__move_repository = GeneralFileRepository(Move, "a")
        self.__move_repository.add(Move(0, 0, 0, 'X'))
        self.__move_repository.add(Move(1, 1, 1, 'X'))
        self.__move_repository.add(Move(2, 2, 2, 'X'))
        self.__move_repository.add(Move(3, 3, 3, 'X'))

    def test_is_valid_move(self):
        move = Move(0, -1, 0, 'X')
        self.assertEqual(GameUtils.is_valid_move(self.__move_repository, move), False)
        move = Move(4, 3, 3, 'O')
        self.assertEqual(GameUtils.is_valid_move(self.__move_repository, move), False)
        move = Move(4, 4, 4, 'O')
        self.assertEqual(GameUtils.is_valid_move(self.__move_repository, move), True)

    def test_winner(self):
        move = Move(4, 4, 4, 'X')
        self.assertEqual(GameUtils.get_winner(self.__move_repository), -1)
        self.__move_repository.add(move)
        self.assertEqual(GameUtils.get_winner(self.__move_repository), 0)

class AITests(unittest.TestCase):
    def setUp(self):
        self.__move_repository = GeneralFileRepository(Move, "a")
        self.__ai = AI(self.__move_repository)

    def test_immediate_win1(self):
        self.__move_repository.add(Move(0, 0, 0, 'X'))
        self.__move_repository.add(Move(1, 1, 1, 'X'))
        self.__move_repository.add(Move(2, 2, 2, 'X'))
        self.__move_repository.add(Move(3, 3, 3, 'X'))
        self.assertEqual(self.__ai.get_move(), Move(4, 4, 4, 'O'))

    def test_immediate_win2(self):
        self.__move_repository.add(Move(0, 0, 5, 'O'))
        self.__move_repository.add(Move(1, 1, 4, 'O'))
        self.__move_repository.add(Move(2, 2, 3, 'O'))
        self.__move_repository.add(Move(3, 3, 2, 'O'))
        self.assertEqual(self.__ai.get_move(), Move(4, 4, 1, 'X'))

    def test_random_move(self):
        cnt_strange = 0
        for i in range(0, 20):
            cnt_strange += (1 if self.__ai.get_move() == self.__ai.get_move() else 0)
        self.assertLessEqual(cnt_strange, 2)

class GameControllerTests(unittest.TestCase):
    def setUp(self):
        self.__move_repository = GeneralFileRepository(Move, "a")
        self.__game_controller = GameController(self.__move_repository)
        self.__move_repository.add(Move(0, 0, 0, 'X'))
        self.__move_repository.add(Move(1, 1, 1, 'X'))
        self.__move_repository.add(Move(2, 2, 2, 'X'))
        self.__move_repository.add(Move(3, 3, 3, 'X'))

    def test_get_turn(self):
        self.assertEqual(self.__game_controller.get_turn(), 0)
        self.__move_repository.add(Move(4, 4, 4, 'X'))
        self.assertEqual(self.__game_controller.get_turn(), 1)

    def test_get_board_as_matrix(self):
        self.assertEqual(self.__game_controller.get_board_as_matrix(),
                         [['X', ' ', ' ', ' ', ' ', ' '],
                         [' ', 'X', ' ', ' ', ' ', ' '],
                         [' ', ' ', 'X', ' ', ' ', ' '],
                         [' ', ' ', ' ', 'X', ' ', ' '],
                         [' ', ' ', ' ', ' ', ' ', ' '],
                         [' ', ' ', ' ', ' ', ' ', ' ']]
                         )
    def test_process_move(self):
        with self.assertRaises(AppException):
            self.__game_controller.process_move(-1, 0, 0, 2)
        self.__game_controller.process_move(4, 4, 4, 'O')
        self.assertEqual(self.__move_repository.get_all(), [
            Move(0, 0, 0, 'X'),
            Move(1, 1, 1, 'X'),
            Move(2, 2, 2, 'X'),
            Move(3, 3, 3, 'X'),
            Move(4, 4, 4, 'O')
        ])