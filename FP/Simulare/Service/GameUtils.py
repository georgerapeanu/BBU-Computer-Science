from Domain.Exceptions import GameException
from Domain.Move import Move
from Repository.GeneralFileRepository import GeneralFileRepository


class GameUtils:
    @staticmethod
    def is_valid_move(move_repository, move):
        """ Checks if a move is valid

        :param move_repository: repository containing all moves
        :type move_repository: GeneralFileRepository
        :param move: Move
        :return: True if valid else False
        """

        if move.x < 0 or move.x >= 6 or move.y < 0 or move.y >= 6:
            return False

        for repo_move in move_repository.get_all():
            if repo_move.x == move.x and repo_move.y == move.y:
                return False
        return True

    @staticmethod
    def get_dictionary_corresponding_to_state(move_repository):
        """ Gets a dictionary that maps moves from coordinates to move

        :param move_repository: repository containing all moves
        :type move_repository: GeneralFileRepository
        :return: dict
        """

        ans = {}

        for move in move_repository.get_all():
            ans[(move.x, move.y)] = move
        return ans

    @staticmethod
    def get_winner(move_repository):
        """ Returns the winner if the game is won by anybody

        :param move_repository: repository containing all moves
        :type move_repository: GeneralFileRepository
        :return: 0 if 1st player winns, 1 if second, -1 if undecided
        """
        moves = GameUtils.get_dictionary_corresponding_to_state(move_repository)

        for i in range(0, 6):
            for j in range(0, 6):
                if j + 5 <= 6:
                    ok = True
                    for k in range(j, j + 5):
                        if (i, k) not in moves:
                            ok = False
                            break
                        if moves[(i, k)].value != moves[(i, j)].value:
                            ok = False
                            break
                    if ok:
                        return 0
                if i + 5 <= 6:
                    ok = True
                    for k in range(i, i + 5):
                        if (k, j) not in moves:
                            ok = False
                            break
                        if moves[(k, j)].value != moves[(i, j)].value:
                            ok = False
                            break
                    if ok:
                        return 0
                if i + 5 <= 6 and j + 5 <= 6:
                    ok = True
                    for k in range(0, 5):
                        if (i + k, j + k) not in moves:
                            ok = False
                            break
                        if moves[(i + k, j + k)].value != moves[(i, j)].value:
                            ok = False
                            break
                    if ok:
                        return 0
                if i + 5 <= 6 and j - 5 >= -1:
                    ok = True
                    for k in range(0, 5):
                        if (i + k, j - k) not in moves:
                            ok = False
                            break
                        if moves[(i + k, j - k)].value != moves[(i, j)].value:
                            ok = False
                            break
                    if ok:
                        return 0
        if len(move_repository.get_all()) == 36:
            return 1
        return -1
