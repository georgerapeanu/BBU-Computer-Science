import random
from copy import deepcopy

from Domain.GameData import GameData
from Domain.Move import Move
from Domain.MoveStatus import MoveStatus
from Domain.PlayerData import PlayerData
from Service.SeekAndDestroyAI import SeekAndDestroyAI
from Service.SeekAndDestroyAIEnum import SeekAndDestroyAICellEnum


class RipAndTearAI(SeekAndDestroyAI):

    def __init__(self, player_data, game_data):
        """ Constructor for RipAndTearAI

        :param player_data: player data
        :type player_data: PlayerData
        :param game_data: game data
        :type game_data: GameData
        """
        super().__init__(player_data, game_data)
        self.__coef_make_hit = 10
        self.__coef_reduce_state = 1
        self.__considered_sizes = deepcopy(game_data.initial_battleships_sizes)

    def __evaluate_no_hit_position(self, miss_dictionary):
        """ This method returns a rough of estimate of the number of placement  on a board with no hits

        :param miss_dictionary: a dictionary that maps (x, y) -> Move
        :type miss_dictionary: dict
        :return: the estimated number of states(int)
        """
        ans = 1

        d = [[0, 1], [1, 0]]
        for size in self.__considered_sizes:
            possible_positions = 0
            for i in range(0, self._game_data.grid_size):
                for j in range(0, self._game_data.grid_size):
                    for k in range(0, len(d)):
                        can_place = True
                        for l in range(0, size):
                            (x, y) = (i + l * d[k][0], j + l * d[k][1])
                            if (x, y) in miss_dictionary or \
                                x < 0 or \
                                x >= self._game_data.grid_size or \
                                y < 0 or \
                                y >= self._game_data.grid_size:
                                can_place = False
                                break
                        if can_place:
                            possible_positions += 1
            ans *= possible_positions
        return ans

    def __backtracking_through_configurations(self, index, miss_dictionary, hit_list, sign):
        """ This method implements the inclusion/exclusion algorithm required to consider hits too

        :param index: the index in the hit_list that we're at
        :type index: int
        :param miss_dictionary: a dictionary that maps (x, y) -> Move
        :type miss_dictionary: dict
        :param hit_list: a list of moves that are hits
        :type hit_list: list
        :param sign: -1 or 1 depending on inclusion/exclusion coefficient
        :type sign: int
        :return: number of configurations(int)
        """
        if index >= len(hit_list):
            return self.__evaluate_no_hit_position(miss_dictionary) * sign

        ans = 0
        ans += self.__backtracking_through_configurations(index + 1, miss_dictionary, hit_list, sign)
        move = hit_list[index]
        miss_dictionary[(move.x, move.y)] = move
        ans += self.__backtracking_through_configurations(index + 1, miss_dictionary, hit_list, -1 * sign)
        del miss_dictionary[(move.x, move.y)]
        return ans

    def __evaluate_position(self, miss_dictionary, hit_list):
        """ This method evaluates the number of positions for the given arguments

        :param miss_dictionary: a dictionary that maps (x, y) -> Move
        :type miss_dictionary: dict
        :param hit_list: a list of moves that are hits
        :type hit_list: list
        :return: number of configurations(int)
        """
        return self.__backtracking_through_configurations(0, miss_dictionary, hit_list, 1)

    def get_best_move(self):
        self._load_cell_states()
        hit_list = []
        miss_dict = {}
        all_moves = self._player_data.moves_repository.list()
        coords_to_move = {}
        for move in all_moves:
            coords_to_move[(move.x, move.y)] = move
        for coords in self._cell_states.keys():
            if self._cell_states[coords] == SeekAndDestroyAICellEnum.HIT:
                hit_list.append(coords_to_move[coords])
            else:
                miss_dict[coords] = coords_to_move[coords]

        weighted_moves = []

        for i in range(0, self._game_data.grid_size):
            for j in range(0, self._game_data.grid_size):
                if (i, j) in coords_to_move:
                    continue
                tmp_move = Move(len(self._player_data.moves_repository), self._player_data.player_id, i, j, MoveStatus.PENDING)

                tmp_move.status = MoveStatus.MISS
                miss_dict[(tmp_move.x, tmp_move.y)] = tmp_move
                miss_states = self.__evaluate_position(miss_dict, hit_list)
                del miss_dict[(tmp_move.x, tmp_move.y)]

                tmp_move.status = MoveStatus.HIT
                hit_list.append(tmp_move)
                hit_states = self.__evaluate_position(miss_dict, hit_list)
                hit_list.pop()
                weighted_moves.append((self.__coef_make_hit * (hit_states - miss_states) - self.__coef_reduce_state * abs(miss_states - hit_states), (i, j)))

        weighted_moves = sorted(weighted_moves, key=lambda x: x[0], reverse=True)
        real_move = Move(len(self._player_data.moves_repository), self._player_data.player_id, 0, 0, MoveStatus.PENDING)
#        if len(weighted_moves) == 0:
#            raise Exception("we have no moves")
        if len(weighted_moves) > 1:
            if random.randint(0, 5) == 5: #just so it isn't so predictable
                tmp = weighted_moves[0]
                weighted_moves[0] = weighted_moves[1]
                weighted_moves[1] = tmp
        real_move.x, real_move.y = weighted_moves[0][1][0], weighted_moves[0][1][1]
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

        good_d = []

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
                good_d.append(d[k])
        if len(good_d) == 1:
            for l in range(0, size):
                self._discovered_battleship_cells[(x + good_d[0][0] * l, y + good_d[0][1] * l)] = 1
            new_considered_sizes = []
            found_equal_size = False
            for x in self.__considered_sizes:
                if size == x:
                    if found_equal_size:
                        new_considered_sizes.append(x)
                    found_equal_size = True
                else:
                    new_considered_sizes.append(x)
            self.__considered_sizes = new_considered_sizes
