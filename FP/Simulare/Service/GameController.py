from Domain.Exceptions import GeneralFileRepositoryException, GameException
from Domain.Move import Move
from Repository.GeneralFileRepository import GeneralFileRepository
from Service.GameUtils import GameUtils


class GameController:
    """ This class implements GameController

    """

    def __init__(self, move_repository):
        """ Constructor for GameController instance

        :param move_repository: the repository containing the moves
        :type move_repository: GeneralFileRepository
        """
        self.__move_repository = move_repository

    def get_turn(self):
        """ This method return 0 if it is the player's turn to move and 1 if it is the computer's

        :return: int
        """
        return len(self.__move_repository.get_all()) % 2

    def process_move(self, id, x, y, value):
        """ Processes move given by UI

        :param id: the id of the move
        :type id: int
        :param x: the first coordinate of the move
        :type x: int
        :param y: the second coordinate of the move
        :type y: int
        :param value: the token that is placed in this cell
        :type value: str
        :return: None
        """

        move = Move(id, x, y, value)
        if not GameUtils.is_valid_move(self.__move_repository, move):
            raise GameException("Move is invalid")
        try:
            self.__move_repository.add(move)
        except GeneralFileRepositoryException:
            raise GameException("Move invalid")

    def get_winner(self):
        return GameUtils.get_winner(self.__move_repository)

    def get_board_as_matrix(self):
        """ Returns board as a matrix of strings

        :return: list
        """
        ans = []
        for i in range(0, 6):
            line = []
            for j in range(0, 6):
                line.append(' ')
            ans.append(line)

        for move in self.__move_repository.get_all():
            ans[move.x][move.y] = move.value
        return ans

    def save(self):
        self.__move_repository.save()

    def get_last_move(self):
        id = len(self.__move_repository.get_all()) - 1
        return self.__move_repository.get_by_id(id)

    def get_next_id(self):
        return len(self.__move_repository.get_all())
