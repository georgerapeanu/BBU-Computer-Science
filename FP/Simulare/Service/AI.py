import random
from copy import deepcopy

from Domain.Move import Move
from Repository.GeneralFileRepository import GeneralFileRepository
from Service.GameUtils import GameUtils


class AI:
    """ This class implements AI. Can be extended with inheritance

    """
    def __init__(self, move_repository):
        """ Constructor for AI instance

        :param move_repository: the repository containing the moves
        :type move_repository: GeneralFileRepository
        """

        self.__move_repository = move_repository

    def get_move(self):
        """ This checks if there is a move that leads to immediate victory.
            If it is, it plays the exact oposite move in the same place(i.e if X is needed for victory, plays O and viceversa)
            If both lead to victory, human is unstoppable
            If no immediate victory, return a move at random
        :return: Move
        """
        moves = GameUtils.get_dictionary_corresponding_to_state(self.__move_repository)
        considered_win_moves = []
        free_moves = []
        for i in range(0, 6):
            for j in range(0, 6):
                move = Move(len(self.__move_repository.get_all()), i, j, 'O')
                if not GameUtils.is_valid_move(self.__move_repository, move):
                    continue
                free_moves.append(deepcopy(move))
                self.__move_repository.add(deepcopy(move))
                if GameUtils.get_winner(self.__move_repository) == 0:
                    considered_win_moves.append(deepcopy(move))
                self.__move_repository.delete_by_id(move.id)
                move.value = 'X'
                free_moves.append(deepcopy(move))
                self.__move_repository.add(deepcopy(move))
                if GameUtils.get_winner(self.__move_repository) == 0:
                    considered_win_moves.append(deepcopy(move))
                self.__move_repository.delete_by_id(move.id)
        if len(considered_win_moves) > 0:
            move = considered_win_moves[random.randrange(0, len(considered_win_moves))]
            move.value = ('O' if move.value == 'X' else 'X')
            return move

        return free_moves[random.randrange(0, len(free_moves))]
