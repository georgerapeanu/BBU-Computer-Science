import random

from Domain.Move import Move
from Domain.MoveStatus import MoveStatus
from Service.GameUtils import GameUtils
from Service.RandomAI import RandomAI
from Service.SeekAndDestroyAIEnum import SeekAndDestroyAICellEnum


class SeekAndDestroyAI(RandomAI):
    """ Improved random ai
        Still places its battleships randomly, but once it shoots something it wile SEEK AND DESTROY
        Also shoots only the cells who's coordinate sum modulo smallest_ship are 0(every remaining battleship should contain one)

    """

    def __init__(self, player_data, game_data):
        super().__init__(player_data, game_data)
        self._cell_states = {}
        self._discovered_battleship_cells = {}
        self._last_move = Move(0, player_data.player_id, 0, 0, MoveStatus.PENDING)

    def _load_cell_states(self):
        self._cell_states = {}
        for move in self._player_data.moves_repository.list():
            if (move.x, move.y) in self._discovered_battleship_cells:
                self._cell_states[(move.x, move.y)] = SeekAndDestroyAICellEnum.FOUND
            elif move.status == MoveStatus.HIT:
                self._cell_states[(move.x, move.y)] = SeekAndDestroyAICellEnum.HIT
            elif move.status == MoveStatus.MISS:
                self._cell_states[(move.x, move.y)] = SeekAndDestroyAICellEnum.MISS

    def __get_next_non_hit_in_direction(self, x, y, d):
        while (x, y) in self._cell_states and self._cell_states[(x, y)] == SeekAndDestroyAICellEnum.HIT:
            x += d[0]
            y += d[1]
        return x, y

    def __select_biased_random(self, n):
        """ Returns an integer between 0 and n - 1 with a bias towards the lower values.
            In order to obtain the bias, we will roll 2n times a random value and return the minimum of them
            The probability density function looks like this: https://www.desmos.com/calculator/ufrkc5pzui
        :param n: the size of the array
        :return: int
        """
        if n == 1:
            return 0
        ans = n - 1
        for i in range(0, 2 * n):
            tmp = random.randrange(0, n)
            if tmp < ans:
                ans = tmp
        return ans

    def __get_smallest_enemy_alive_ship(self):
        ans = None
        for battleship_mask in self._player_data.opponent_mask_repository.list():
            if ans is None or battleship_mask.size < ans:
                ans = battleship_mask.size
        return ans

    def get_best_move(self):
        self._load_cell_states()
        d = [(-1, 0), (0, 1), (1, 0), (0, -1)]
        weighted_moves = {}
        smallest_size = self.__get_smallest_enemy_alive_ship()
        for i in range(0, self._game_data.grid_size):
            for j in range(0, self._game_data.grid_size):
                if (i, j) in self._cell_states and self._cell_states[(i, j)] == SeekAndDestroyAICellEnum.HIT:
                    for k in range(0, len(d)):
                        x, y = self.__get_next_non_hit_in_direction(i, j, d[k])
                        move = Move(len(self._player_data.moves_repository), self._player_data.player_id, x, y, MoveStatus.PENDING)
                        if GameUtils.is_valid_move(self._game_data.grid_size, self._player_data.moves_repository, move) is False:
                            continue
                        if (x, y) not in weighted_moves:
                            weighted_moves[(x, y)] = 0
                        weighted_moves[(x, y)] += 1
        if len(weighted_moves) == 0:
            for move in GameUtils.get_possible_moves(self._game_data.grid_size, self._player_data.moves_repository):
                x, y = move.x, move.y
                if (x + y) % smallest_size != 0:
                    continue
                weighted_moves[(x, y)] = 1

        move_list = []
        weights = []
        for coords in weighted_moves.keys():
            real_move = Move(len(self._player_data.moves_repository), self._player_data.player_id, coords[0], coords[1], MoveStatus.PENDING)
            move_list.append((weighted_moves[coords], real_move))
            weights.append(weighted_moves[coords])
        weights = list(reversed(list(set(weights))))
        target_weight = weights[self.__select_biased_random(len(weights))]
        move_list = list(filter(lambda x: x[0] == target_weight, move_list))

        real_move = move_list[random.randrange(0, len(move_list))][1]
        self._last_move = real_move
        return real_move

    def notify_last_move_destroyed_ship(self, size):
#        if self._last_move.status == MoveStatus.PENDING:
#            raise Exception("Something went wrong AI got notified before actual move")

        if size is None:
            return

        self._load_cell_states()

        x = self._last_move.x
        y = self._last_move.y
        d = [(-1, 0), (0, 1), (1, 0), (0, -1)]

        for k in range(0, len(d)):
            ok_direction = True
            for l in range(0, size):
                xx, yy = x + d[k][0] * l, y + d[k][1] * l
                if xx < 0 or xx >= self._game_data.grid_size:
                    ok_direction = False
                    break

                if yy < 0 or yy >= self._game_data.grid_size:
                    ok_direction = False
                    break

                if (xx, yy) not in self._cell_states or \
                        self._cell_states[(x + d[k][0] * l, y + d[k][1] * l)] != SeekAndDestroyAICellEnum.HIT:
                    ok_direction = False
                    break

            if ok_direction:
                for l in range(0, size):
                    self._discovered_battleship_cells[(x + d[k][0] * l, y + d[k][1] * l)] = 1
                break
