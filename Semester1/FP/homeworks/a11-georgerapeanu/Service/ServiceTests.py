import unittest

from Domain.Battleship import Battleship
from Domain.BattleshipMask import BattleshipMask
from Domain.BattleshipOrientation import BattleshipOrientation
from Domain.GameData import GameData
from Domain.Move import Move
from Domain.MoveStatus import MoveStatus
from Domain.PlayerData import PlayerData
from Repository.GeneralRepository import GeneralRepository
from Service.ModelAI import ModelAI
from Service.GameController import GameController
from Service.GameUtils import GameUtils
from Service.GenericPlayer import GenericPlayer
from Service.RandomAI import RandomAI
from Service.RipAndTearAI import RipAndTearAI
from Service.SeekAndDestroyAI import SeekAndDestroyAI
from Service.ServiceExceptions import GameControllerException


class GameUtilsTests(unittest.TestCase):
    def setUp(self):
        self.grid_size = 2
        self.move_repository = GeneralRepository()

    def test_move_id_exists_raises(self):
        self.move_repository.add(Move(1, 0, 0, 0, MoveStatus.PENDING))
        move = Move(1, 0, 1, 1, MoveStatus.PENDING)
        self.assertEqual(GameUtils.is_valid_move(self.grid_size, self.move_repository, move), False)

    def test_get_possible_moves(self):
        self.move_repository.add(Move(1, 0, 0, 0, MoveStatus.PENDING))
        self.assertEqual(GameUtils.get_possible_moves(self.grid_size, self.move_repository),
                         [Move(0, 0, 0, 1, MoveStatus.PENDING),
                          Move(0, 0, 1, 0, MoveStatus.PENDING),
                          Move(0, 0, 1, 1, MoveStatus.PENDING)])


class GameControllerPlacementTests(unittest.TestCase):
    def setUp(self):
        self.game_data = GameData(10, [2, 3])
        self.p1_battleship_repository = GeneralRepository()
        self.p2_battleship_repository = GeneralRepository()
        self.p1_move_repository = GeneralRepository()
        self.p2_move_repository = GeneralRepository()
        self.p1_battleship_mask_repository = GeneralRepository()
        self.p2_battleship_mask_repository = GeneralRepository()
        for i in range(0, len(self.game_data.initial_battleships_sizes)):
            size = self.game_data.initial_battleships_sizes[i]
            self.p1_battleship_mask = BattleshipMask(i, size, False)
            self.p1_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            self.p2_battleship_mask = BattleshipMask(i, size, False)
            self.p2_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            self.p1_battleship_repository.add(self.p1_battleship)
            self.p2_battleship_repository.add(self.p2_battleship)
            self.p1_battleship_mask_repository.add(self.p2_battleship_mask)
            self.p2_battleship_mask_repository.add(self.p1_battleship_mask)
        self.p1_data = PlayerData(0, self.p1_battleship_repository, self.p1_move_repository, self.p1_battleship_mask_repository)
        self.p2_data = PlayerData(1, self.p2_battleship_repository, self.p2_move_repository, self.p2_battleship_mask_repository)

        self.player1 = GenericPlayer(self.p1_data)
        self.player2 = GenericPlayer(self.p2_data)

        self.game_controller = GameController(self.game_data, self.p1_data, self.p2_data)

    def test_get_placed_battleship_count(self):
        self.assertEqual(self.game_controller.get_placed_battleships_count(0), 0)
        self.assertEqual(self.game_controller.get_placed_battleships_count(1), 0)
        self.game_controller.place_player_battleship_from_raw(0, 0, 1, 1, BattleshipOrientation.VERTICAL)
        self.assertEqual(self.game_controller.get_placed_battleships_count(0), 1)

    def test_is_battleship_placement_done(self):
        self.assertEqual(self.game_controller.is_battleship_placement_done(), False)
        self.game_controller.place_player_battleship_from_raw(0, 0, 1, 1, BattleshipOrientation.VERTICAL)
        self.game_controller.place_player_battleship_from_raw(0, 1, 1, 2, BattleshipOrientation.VERTICAL)
        self.game_controller.mark_done_placement(0)
        self.assertEqual(self.game_controller.is_battleship_placement_done(), False)
        self.game_controller.place_player_battleship_from_raw(1, 0, 1, 1, BattleshipOrientation.VERTICAL)
        self.game_controller.place_player_battleship_from_raw(1, 1, 1, 2, BattleshipOrientation.VERTICAL)
        self.game_controller.mark_done_placement(1)
        self.assertEqual(self.game_controller.is_battleship_placement_done(), True)

    def test_place_player_battleship(self):

        self.game_controller.place_player_battleship_from_raw(0, 0, 1, 1, BattleshipOrientation.VERTICAL)

        with self.assertRaises(GameControllerException):
            self.game_controller.place_player_battleship_from_raw(0, 1, 1, 1, BattleshipOrientation.VERTICAL)

        with self.assertRaises(GameControllerException):
            self.game_controller.mark_done_placement(0)

        self.game_controller.place_player_battleship_from_raw(0, 1, 1, 2, BattleshipOrientation.VERTICAL)

        with self.assertRaises(GameControllerException):
            self.game_controller.place_player_battleship_from_raw(0, 3, 1, 2, BattleshipOrientation.VERTICAL)

        with self.assertRaises(GameControllerException):
            battleship = Battleship(3, 1, False, 3, 3, BattleshipOrientation.HORIZONTAL, False)
            self.game_controller.place_player_battleship(0, battleship)

        with self.assertRaises(GameControllerException):
            battleship = Battleship(0, 1, False, 3, 3, BattleshipOrientation.HORIZONTAL, False)
            self.game_controller.place_player_battleship(0, battleship)

        with self.assertRaises(GameControllerException):
            self.game_controller.place_player_battleship_from_raw(1, 0, 1, 1, BattleshipOrientation.VERTICAL)

        self.game_controller.reset_battleship(0, 0)
        with self.assertRaises(GameControllerException):
            self.game_controller.reset_battleship(0, 3)
        self.game_controller.place_player_battleship_from_raw(0, 0, 1, 1, BattleshipOrientation.VERTICAL)
        self.game_controller.mark_done_placement(0)

        with self.assertRaises(GameControllerException):
            battleship = Battleship(0, 1, False, 3, 3, BattleshipOrientation.HORIZONTAL, False)
            self.game_controller.place_player_battleship(1, battleship)

        self.game_controller.place_player_battleship_from_raw(1, 0, 1, 1, BattleshipOrientation.VERTICAL)
        with self.assertRaises(GameControllerException):
            self.game_controller.place_player_battleship_from_raw(1, 1, 20, 20, BattleshipOrientation.VERTICAL)
        self.game_controller.place_player_battleship_from_raw(1, 1, 1, 2, BattleshipOrientation.VERTICAL)
        self.game_controller.mark_done_placement(1)

        with self.assertRaises(GameControllerException):
            self.game_controller.place_player_battleship_from_raw(0, 1, 1, 2, BattleshipOrientation.VERTICAL)

    def test_grid_size(self):
        self.assertEqual(self.game_controller.get_grid_size(), 10)

    def test_turn_raises(self):
        with self.assertRaises(GameControllerException):
            self.game_controller.get_turn()

    def test_make_move_raises(self):
        with self.assertRaises(GameControllerException):
            self.game_controller.make_player_move_from_raw(0, 0, 0)


class GameControllerGameTests(unittest.TestCase):
    def setUp(self):
        self.game_data = GameData(10, [2, 3])
        self.p1_battleship_repository = GeneralRepository()
        self.p2_battleship_repository = GeneralRepository()
        self.p1_move_repository = GeneralRepository()
        self.p2_move_repository = GeneralRepository()
        self.p1_battleship_mask_repository = GeneralRepository()
        self.p2_battleship_mask_repository = GeneralRepository()
        for i in range(0, len(self.game_data.initial_battleships_sizes)):
            size = self.game_data.initial_battleships_sizes[i]
            self.p1_battleship_mask = BattleshipMask(i, size, False)
            self.p1_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            self.p2_battleship_mask = BattleshipMask(i, size, False)
            self.p2_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            self.p1_battleship_repository.add(self.p1_battleship)
            self.p2_battleship_repository.add(self.p2_battleship)
            self.p1_battleship_mask_repository.add(self.p2_battleship_mask)
            self.p2_battleship_mask_repository.add(self.p1_battleship_mask)
        self.p1_data = PlayerData(0, self.p1_battleship_repository, self.p1_move_repository, self.p1_battleship_mask_repository)
        self.p2_data = PlayerData(1, self.p2_battleship_repository, self.p2_move_repository, self.p2_battleship_mask_repository)

        self.player1 = GenericPlayer(self.p1_data)
        self.player2 = GenericPlayer(self.p2_data)

        self.game_controller = GameController(self.game_data, self.p1_data, self.p2_data)
        self.game_controller.place_player_battleship_from_raw(0, 0, 1, 1, BattleshipOrientation.VERTICAL)
        self.game_controller.place_player_battleship_from_raw(0, 1, 1, 2, BattleshipOrientation.VERTICAL)
        self.game_controller.mark_done_placement(0)
        self.game_controller.place_player_battleship_from_raw(1, 0, 1, 1, BattleshipOrientation.VERTICAL)
        self.game_controller.place_player_battleship_from_raw(1, 1, 1, 2, BattleshipOrientation.VERTICAL)
        self.game_controller.mark_done_placement(1)

    def test_get_last_move(self):
        self.game_controller.make_player_move_from_raw(0, 0, 0)
        self.assertEqual(self.game_controller.get_last_move(), Move(0, 0, 0, 0, MoveStatus.MISS))

    def test_make_move(self):
        self.game_controller.make_player_move_from_raw(0, 0, 0)
        self.assertEqual(self.player1.get_moves(), [Move(0, 0, 0, 0, MoveStatus.MISS)])

    def test_get_live_battleships_count(self):
        self.game_controller.make_player_move_from_raw(0, 0, 0)
        with self.assertRaises(GameControllerException):
            self.game_controller.make_player_move_from_raw(0, 1, 1)
        self.game_controller.make_player_move_from_raw(1, 1, 1)
        self.game_controller.make_player_move_from_raw(1, 1, 2)
        self.assertEqual(self.game_controller.get_player_live_battleships_count(0), 2)
        self.game_controller.make_player_move_from_raw(1, 2, 1)
        self.assertEqual(self.game_controller.get_player_live_battleships_count(0), 1)
        self.game_controller.make_player_move_from_raw(1, 2, 2)
        self.assertEqual(self.game_controller.get_winner(), -1)
        self.game_controller.make_player_move_from_raw(1, 3, 2)
        self.assertEqual(self.game_controller.get_player_live_battleships_count(0), 0)
        self.assertEqual(self.game_controller.get_winner(), 1)

    def test_not_your_turn_yet_raises(self):
        self.game_controller.make_player_move_from_raw(0, 2, 2)
        with self.assertRaises(GameControllerException):
            self.game_controller.make_player_move_from_raw(1, 2, 2)

    def test_last_destroyed_battleship_size(self):
        self.game_controller.make_player_move_from_raw(0, 1, 2)
        self.game_controller.make_player_move_from_raw(0, 2, 2)
        self.assertEqual(self.game_controller.get_last_move_destroyed_battleship_size(), None)
        self.game_controller.make_player_move_from_raw(0, 3, 2)
        self.assertEqual(self.game_controller.get_last_move_destroyed_battleship_size(), 3)
        self.game_controller.make_player_move_from_raw(0, 1, 1)
        self.assertEqual(self.game_controller.get_last_move_destroyed_battleship_size(), None)
        self.game_controller.make_player_move_from_raw(0, 2, 1)
        self.assertEqual(self.game_controller.get_last_move_destroyed_battleship_size(), 2)
        self.assertEqual(self.game_controller.get_winner(), 0)

    def test_move_duplicate_raises(self):
        self.game_controller.make_player_move_from_raw(0, 2, 2)
        with self.assertRaises(GameControllerException):
            self.game_controller.make_player_move_from_raw(0, 2, 2)

    def test_get_turn(self):
        self.assertEqual(self.game_controller.get_turn(), 0)
        self.game_controller.make_player_move_from_raw(0, 0, 0)
        self.assertEqual(self.game_controller.get_turn(), 1)
        self.game_controller.make_player_move_from_raw(1, 0, 0)
        self.assertEqual(self.game_controller.get_turn(), 0)
        self.game_controller.make_player_move_from_raw(0, 1, 2)
        self.assertEqual(self.game_controller.get_turn(), 0)

    def test_invalid_move_raises(self):
        with self.assertRaises(GameControllerException):
            self.game_controller.make_player_move(Move(0, 0, -1, -1, MoveStatus.PENDING))

    def test_get_player_battleship_masks(self):
        self.assertEqual(self.game_controller.get_player_battleship_masks(0), [BattleshipMask(0, 2, False),
                                                                               BattleshipMask(1, 3, False)])
        self.game_controller.make_player_move_from_raw(0, 1, 1)
        self.game_controller.make_player_move_from_raw(0, 2, 1)
        self.assertEqual(self.game_controller.get_player_battleship_masks(0),
                         [BattleshipMask(0, 2, True), BattleshipMask(1, 3, False)])


class RandomAITests(unittest.TestCase):
    """ You really can't test a random AI better

    """
    def setUp(self):
        self.game_data = GameData(10, [2, 3, 3, 4, 5])
        self.p1_battleship_repository = GeneralRepository()
        self.p1_move_repository = GeneralRepository()
        self.p1_battleship_mask_repository = GeneralRepository()
        for i in range(0, len(self.game_data.initial_battleships_sizes)):
            size = self.game_data.initial_battleships_sizes[i]
            p1_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            p2_battleship_mask = BattleshipMask(i, size, False)
            self.p1_battleship_repository.add(p1_battleship)
            self.p1_battleship_mask_repository.add(p2_battleship_mask)

        self.p1_data = PlayerData(0, self.p1_battleship_repository, self.p1_move_repository, self.p1_battleship_mask_repository)
        self.player = RandomAI(self.p1_data, self.game_data)

    def test_finishes_placement(self):
        for i in range(0, 1000):
            self.player.place_battleships()
            count = 0
            for battleship in self.player.get_battleships():
                count += (1 if battleship.placed else 0)
                battleship.placed = False
                self.p1_battleship_repository.update(battleship.id, battleship)
            self.assertEqual(count, len(self.game_data.initial_battleships_sizes))

    def test_acquires_move(self):
        self.assertEqual(isinstance(self.player.get_best_move(), Move), True)


class ModelAITests(unittest.TestCase):
    def setUp(self):
        self.game_data = GameData(10, [2, 3, 3, 4, 5])
        self.p1_battleship_repository = GeneralRepository()
        self.p1_move_repository = GeneralRepository()
        self.p1_battleship_mask_repository = GeneralRepository()
        for i in range(0, len(self.game_data.initial_battleships_sizes)):
            size = self.game_data.initial_battleships_sizes[i]
            p1_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            p2_battleship_mask = BattleshipMask(i, size, False)
            self.p1_battleship_repository.add(p1_battleship)
            self.p1_battleship_mask_repository.add(p2_battleship_mask)

        self.p1_data = PlayerData(0, self.p1_battleship_repository, self.p1_move_repository, self.p1_battleship_mask_repository)
        self.player = ModelAI(self.p1_data, self.game_data)

    def test_finishes_placement(self):
        for i in range(0, 100):
            self.player.place_battleships()
            for battleship in self.player.get_battleships():
                battleship.placed = False
                self.p1_battleship_repository.update(battleship.id, battleship)

    def test_acquires_move(self):
        self.player.get_best_move()

    def test_notifiy(self):
        self.player.notify_last_move_destroyed_ship(2)


class GenericPlayerTests(unittest.TestCase):
    def setUp(self):
        sizes = [2]
        p1_battleship_repository = GeneralRepository()
        p1_move_repository = GeneralRepository()
        p1_battleship_mask_repository = GeneralRepository()
        for i in range(0, len(sizes)):
            size = sizes[i]
            p1_battleship_mask = BattleshipMask(i, size, False)
            p1_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            p2_battleship_mask = BattleshipMask(i, size, False)
            p2_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            p1_battleship_repository.add(p1_battleship)
            p1_battleship_mask_repository.add(p2_battleship_mask)

        p1_move_repository.add(Move(1, 0, 0, 0, MoveStatus.PENDING))

        p1_data = PlayerData(0, p1_battleship_repository, p1_move_repository, p1_battleship_mask_repository)
        self.player = GenericPlayer(p1_data)

    def test_get_player_id(self):
        self.assertEqual(self.player.get_player_id(), 0)

    def test_get_moves(self):
        self.assertEqual(self.player.get_moves(), [Move(1, 0, 0, 0, MoveStatus.PENDING)])

    def test_get_battleships(self):
        self.assertEqual(self.player.get_battleships(), [Battleship(0, 2, False, 0, 0, BattleshipOrientation.VERTICAL, False)])


class RipAndTearAITest(unittest.TestCase):
    def setUp(self):
        self.game_data = GameData(5, [2, 3, 3])
        self.p1_battleship_repository = GeneralRepository()
        self.p1_move_repository = GeneralRepository()
        self.p1_battleship_mask_repository = GeneralRepository()
        self.p2_battleship_repository = GeneralRepository()
        self.p2_move_repository = GeneralRepository()
        self.p2_battleship_mask_repository = GeneralRepository()
        for i in range(0, len(self.game_data.initial_battleships_sizes)):
            size = self.game_data.initial_battleships_sizes[i]
            p1_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            p1_battleship_mask = BattleshipMask(i, size, False)
            p2_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            p2_battleship_mask = BattleshipMask(i, size, False)
            self.p1_battleship_repository.add(p1_battleship)
            self.p1_battleship_mask_repository.add(p2_battleship_mask)
            self.p2_battleship_repository.add(p2_battleship)
            self.p2_battleship_mask_repository.add(p1_battleship_mask)

        self.p1_data = PlayerData(0, self.p1_battleship_repository, self.p1_move_repository,
                                  self.p1_battleship_mask_repository)
        self.p2_data = PlayerData(1, self.p2_battleship_repository, self.p2_move_repository,
                                  self.p2_battleship_mask_repository)
        self.player1 = RandomAI(self.p1_data, self.game_data)
        self.player2 = RipAndTearAI(self.p2_data, self.game_data)
        self.game_controller = GameController(self.game_data, self.p1_data, self.p2_data)

    def __play_a_game(self):
        self.player1.place_battleships()
        self.game_controller.mark_done_placement(0)
        self.player2.place_battleships()
        self.game_controller.mark_done_placement(1)
        while self.game_controller.get_winner() == -1:
            if self.game_controller.get_turn() == 0:
                move = self.player1.get_best_move()
                self.game_controller.make_player_move(move)
                self.player1.notify_last_move_destroyed_ship(self.game_controller.get_last_move_destroyed_battleship_size())
            else:
                move = self.player2.get_best_move()
                self.game_controller.make_player_move(move)
                self.player2.notify_last_move_destroyed_ship(self.game_controller.get_last_move_destroyed_battleship_size())
        return self.game_controller.get_winner()

    def test_general(self):
        wins = [0, 0]
        for i in range(0, 10):
            self.setUp()
            wins[self.__play_a_game()] += 1
        self.assertGreater(wins[1], 8)

class SeekAndDestroyAITest(unittest.TestCase):
    def setUp(self):
        self.game_data = GameData(5, [2, 3, 3])
        self.p1_battleship_repository = GeneralRepository()
        self.p1_move_repository = GeneralRepository()
        self.p1_battleship_mask_repository = GeneralRepository()
        self.p2_battleship_repository = GeneralRepository()
        self.p2_move_repository = GeneralRepository()
        self.p2_battleship_mask_repository = GeneralRepository()
        for i in range(0, len(self.game_data.initial_battleships_sizes)):
            size = self.game_data.initial_battleships_sizes[i]
            p1_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            p1_battleship_mask = BattleshipMask(i, size, False)
            p2_battleship = Battleship(i, size, False, 0, 0, BattleshipOrientation.VERTICAL, False)
            p2_battleship_mask = BattleshipMask(i, size, False)
            self.p1_battleship_repository.add(p1_battleship)
            self.p1_battleship_mask_repository.add(p2_battleship_mask)
            self.p2_battleship_repository.add(p2_battleship)
            self.p2_battleship_mask_repository.add(p1_battleship_mask)

        self.p1_data = PlayerData(0, self.p1_battleship_repository, self.p1_move_repository,
                                  self.p1_battleship_mask_repository)
        self.p2_data = PlayerData(1, self.p2_battleship_repository, self.p2_move_repository,
                                  self.p2_battleship_mask_repository)
        self.player1 = RandomAI(self.p1_data, self.game_data)
        self.player2 = SeekAndDestroyAI(self.p2_data, self.game_data)
        self.game_controller = GameController(self.game_data, self.p1_data, self.p2_data)

    def __play_a_game(self):
        self.player1.place_battleships()
        self.game_controller.mark_done_placement(0)
        self.player2.place_battleships()
        self.game_controller.mark_done_placement(1)
        while self.game_controller.get_winner() == -1:
            if self.game_controller.get_turn() == 0:
                move = self.player1.get_best_move()
                self.game_controller.make_player_move(move)
                self.player1.notify_last_move_destroyed_ship(self.game_controller.get_last_move_destroyed_battleship_size())
            else:
                move = self.player2.get_best_move()
                self.game_controller.make_player_move(move)
                self.player2.notify_last_move_destroyed_ship(self.game_controller.get_last_move_destroyed_battleship_size())
        return self.game_controller.get_winner()

    def test_general(self):
        wins = [0, 0]
        for i in range(0, 10):
            self.setUp()
            wins[self.__play_a_game()] += 1
        self.assertGreater(wins[1], 8)
