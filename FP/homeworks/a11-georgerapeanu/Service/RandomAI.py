import random

from Domain.Battleship import Battleship
from Domain.BattleshipOrientation import BattleshipOrientation
from Domain.Move import Move
from Domain.MoveStatus import MoveStatus
from Service.ModelAI import ModelAI
from Service.GameUtils import GameUtils


class RandomAI(ModelAI):
    def __init__(self, player_data, game_data):
        """ Same as ModelAI

        :param player_data:
        :param game_data:
        """
        super().__init__(player_data, game_data)

    def place_battleships(self):
        """Described in ModelAI

        :return:
        """
        for battleship in self.get_battleships():
            turns_since_last_place = 0
            while turns_since_last_place < self._game_data.grid_size:
                turns_since_last_place += 1
                x = random.randrange(0, self._game_data.grid_size)
                y = random.randrange(0, self._game_data.grid_size)
                orientation = BattleshipOrientation.VERTICAL
                if random.randrange(0, 2) == 1:
                    orientation = BattleshipOrientation.HORIZONTAL
                tmp_battleship = Battleship(battleship.id, battleship.size, False, x, y, orientation, True)
                if GameUtils.can_place_battleship(self._game_data.grid_size, self._player_data.battleships_repository, tmp_battleship):
                    tmp_battleship.placed = True
                    self._player_data.battleships_repository.update(tmp_battleship.id, tmp_battleship)
                    turns_since_last_place = 0
                    break
            if self._game_data.grid_size == turns_since_last_place: #Reset everything and try again
                for battleship in self.get_battleships():
                    battleship.placed = False
                    self._player_data.battleships_repository.update(battleship.id, battleship)
                self.place_battleships()
                break

    def get_best_move(self):
        """Described in ModelAI

        :return:
        """
        moves = GameUtils.get_possible_moves(self._game_data.grid_size, self._player_data.moves_repository)
        move = moves[random.randrange(0, len(moves))]
        move = Move(len(self._player_data.moves_repository), self._player_data.player_id, move.x, move.y, MoveStatus.PENDING)
        return move
