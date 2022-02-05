from Domain.Battleship import Battleship
from Domain.Move import Move
from Domain.MoveStatus import MoveStatus
from Repository.GeneralRepository import GeneralRepository


class GameUtils:
    """ A helper class that just checks things in order to avoid duplicate code

    """
    @staticmethod
    def can_place_battleship(grid_size, battleships_repository, battleship):
        """ Checks if placing a battleship is valid(i.e. that it doesnt intersect with any initialised battleship and
        that it doesn't exit the grid
        :param grid_size: the size of the grid
        :type grid_size: int
        :param battleships_repository: repository of battleships
        :type battleships_repository: GeneralRepository
        :param battleship: battleship
        :type battleship: Battleship
        :return: True/False
        """

        battleship_bb = battleship.get_bounding_box()

        if battleship_bb[0] < 0 or battleship_bb[1] < 0 or battleship_bb[2] >= grid_size or battleship_bb[3] >= grid_size:
            return False

        for repo_battleship in battleships_repository.list():
            if not repo_battleship.placed:
                continue
            repo_battleship_bb = repo_battleship.get_bounding_box()
            if battleship_bb[0] > repo_battleship_bb[2] or battleship_bb[2] < repo_battleship_bb[0]:
                continue
            if battleship_bb[1] > repo_battleship_bb[3] or battleship_bb[3] < repo_battleship_bb[1]:
                continue
            return False
        return True

    @staticmethod
    def get_possible_moves(grid_size, moves_repository):
        """ Returns a list of all possible moves that can be applied on the current state
        :param grid_size: the size of the grid
        :type grid_size: int
        :param moves_repository: move repository
        :type moves_repository: GeneralRepository
        :return: list of available moves(only coordinates are valid)
        """

        moves = moves_repository.list()
        existing_moves = {}

        for move in moves:
            existing_moves[(move.x, move.y)] = 1

        ans = []

        for i in range(0, grid_size):
            for j in range(0, grid_size):
                if (i, j) in existing_moves:
                    continue
                ans.append(Move(0, 0, i, j, MoveStatus.PENDING))
        return ans

    @staticmethod
    def __check_move_is_not_duplicate(moves_repository, move):
        """
        Checks that a move has not been done before.
        :param moves_repository: the move repository
        :param move: the move to be checked
        :type move: Move
        :return:
        """

        for repo_move in moves_repository.list():
            if move.x == repo_move.x and move.y == repo_move.y:
                return False
        return True


    @staticmethod
    def is_valid_move(grid_size, moves_repository, move):
        """ Checks if a move is valid
        :param grid_size: the size of the grid
        :type grid_size: int
        :param moves_repository: move repository
        :type moves_repository: GeneralRepository
        :param move: the move to be verified
        :type move: Move
        :return: list of available moves(only coordinates are valid)
        """

        if moves_repository.get_by_id(move.id) is not None:
            return False

        if move.x < 0 or move.x >= grid_size or move.y < 0 or move.y >= grid_size:
            return False

        if GameUtils.__check_move_is_not_duplicate(moves_repository, move) is False:
            return False

        return True
