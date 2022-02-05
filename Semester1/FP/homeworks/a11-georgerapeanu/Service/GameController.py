from Domain.Battleship import Battleship
from Domain.BattleshipMask import BattleshipMask
from Domain.BattleshipOrientation import BattleshipOrientation
from Domain.GameData import GameData
from Domain.Move import Move
from Domain.MoveStatus import MoveStatus
from Domain.PlayerData import PlayerData
from Service.GameUtils import GameUtils
from Service.ServiceExceptions import GameControllerException

# TODO whats single responsibility principle?


class GameController:
    def __init__(self, game_data, player1_data, player2_data):
        """Constructor for the game controller

        :param game_data: holds the current game data
        :type game_data: GameData
        :param player1_data: holds p1 data
        :type player1_data: PlayerData
        :param player2_data: PlayerData
        :type player2_data: PlayerData
        """
        self._game_data = game_data
        self._player_data = [player1_data, player2_data]
        self.__done_placement = [False, False]
        self.__turn = 0
        self.__last_move = None
        self.__last_move_battleship_destroyed_size = None  # size of the last battleship if it was destroyed else None

    def __validate_battleship_placement_player_id(self, player_id):
        """ Checks that the current player is able to make placement. Throws GameControllerException if not

        :param player_id: current player id
        :type player_id: int
        :return:
        """
        if player_id > 0 and self.__done_placement[0] is False:
            raise GameControllerException("First player did not complete his placement")

    def __validate_player_move_player_id(self, player_id):
        """ Checks that the current player is able to make a move now. Throws GameControllerException otherwise

        :param player_id: current player id
        :type player_id: int
        :return:
        """
        if self.__turn != player_id:
            raise GameControllerException("It is not your turn yet")

    def __search_new_destroyed_battleships_for_player(self, player_id):
        """ This method searches and marks as destroyed any battleships that might have gotten destroyed
            Between two consecutive function calls

        :param player_id: current player id
        :type player_id: int
        :return:
        """
        for battleship in self._player_data[player_id].battleships_repository.list():
            if battleship.destroyed:
                continue
            cnt = 0
            for move in self._player_data[1 - player_id].moves_repository.list():
                if battleship.get_bounding_box()[0] <= move.x <= battleship.get_bounding_box()[2]:
                    if battleship.get_bounding_box()[1] <= move.y <= battleship.get_bounding_box()[3]:
                        cnt += 1
            if cnt == battleship.size:
                self.__last_move_battleship_destroyed_size = battleship.size
                battleship.destroyed = True
                self._player_data[player_id].battleships_repository.update(battleship.id, battleship)
                battleship_mask = BattleshipMask(battleship.id, battleship.size, battleship.destroyed)
                self._player_data[1 - player_id].opponent_mask_repository.update(battleship_mask.id, battleship_mask)

    def get_placed_battleships_count(self, player_id):
        """ Returns the number of successfully placed battleships by the player with player_id

        :param player_id: current player id
        :type player_id: int
        :return: number of placed battleships(int)
        """
        return sum(1 if x.placed else 0 for x in self._player_data[player_id].battleships_repository.list())

    def is_battleship_placement_done(self):
        """Checks if both players completed the battleship placement phase

        :return: True/False
        """
        return self.has_done_placement(0) and self.has_done_placement(1)

    def place_player_battleship(self, player_id, battleship):
        """ Attempts to place a battleship for the current player. Raises GameControllerException if placement is invalid

        :param player_id: id of the current player
        :type player_id: int
        :param battleship: battleship that is being placed
        :type battleship: Battleship
        :return:
        """
        self.__validate_battleship_placement_player_id(player_id)

        if self.__done_placement[player_id]:
            raise GameControllerException("Battleship placement phase is over")

        repo_battleship = self._player_data[player_id].battleships_repository.get_by_id(battleship.id)
        if repo_battleship is None:
            raise GameControllerException("Cannot place battleship with specified id")
        if repo_battleship.placed:
            raise GameControllerException("Battleship already placed")
        if repo_battleship.size != battleship.size:
            raise GameControllerException("Battleship mismatch")
        if not GameUtils.can_place_battleship(self._game_data.grid_size, self._player_data[player_id].battleships_repository, battleship):
            raise GameControllerException("Cannot place battleship")

        battleship.placed = True
        battleship_mask = self._player_data[1 - player_id].opponent_mask_repository.get_by_id(battleship.id)
        #if battleship_mask is None: #debug purposes only
        #    raise Exception("App error, battleship_mask with id of a given battleship does not exist")
        battleship_mask.size = battleship.size
        self._player_data[player_id].battleships_repository.update(battleship.id, battleship)
        self._player_data[1 - player_id].opponent_mask_repository.update(battleship_mask.id, battleship_mask)

    def place_player_battleship_from_raw(self, player_id, battleship_id, x, y, orientation):
        """ Makes a battleship and passes it toe place_player_battleship
            UI should call this function

        :param player_id: current player id
        :type player_id: int
        :param battleship_id: battleship being placed id
        :type battleship_id: int
        :param x: x coordinate of the head of the ballteship(upperleft-most corner)
        :type x: int
        :param y: y coordinate of the head of the ballteship(upperleft-most corner)
        :type y: int
        :param orientation: orientation of the battleship
        :type orientation: BattleshipOrientation
        :return:
        """
        battleship = self._player_data[player_id].battleships_repository.get_by_id(battleship_id)
        if battleship is None:
            raise GameControllerException("Battleship with specified id doesn't exist")
        battleship.x = x
        battleship.y = y
        battleship.orientation = orientation
        self.place_player_battleship(player_id, battleship)

    def make_player_move(self, move):
        """ Makes a given move. Raises GameControllerException if the move is invalid

        :param move: the given move
        :type move: Move
        :return:
        """
        self.__validate_player_move_player_id(move.player)
        if not self.is_battleship_placement_done():
            raise GameControllerException("Battleship placement phase is not over")
        if GameUtils.is_valid_move(self._game_data.grid_size, self._player_data[move.player].moves_repository,
                                   move) is False:
            raise GameControllerException("Move is invalid")

        move.status = MoveStatus.MISS
        for battleship in self._player_data[1 - move.player].battleships_repository.list():
            battleship_bb = battleship.get_bounding_box()
            if battleship_bb[0] <= move.x <= battleship_bb[2]:
                if battleship_bb[1] <= move.y <= battleship_bb[3]:
                    move.status = MoveStatus.HIT
                    break
        self._player_data[move.player].moves_repository.add(move)
        self.__last_move = move
        self.__last_move_battleship_destroyed_size = None
        if move.status == MoveStatus.MISS:
            self.__turn = 1 - self.__turn
        else:
            self.__search_new_destroyed_battleships_for_player(1 - move.player)

    def make_player_move_from_raw(self, player_id, x, y):
        """ This method creates and passes the move to make_player_move
            This should be called by the UI

        :param player_id: current player id
        :type player_id: int
        :param x: current move x coordinate
        :type x: int
        :param y: current move y coordinate
        :type y: int
        :return:
        """
        move = Move(len(self._player_data[player_id].moves_repository), player_id, x, y, MoveStatus.PENDING)
        self.make_player_move(move)

    def has_done_placement(self, player_id):
        """ Returns true if the current player has completed his battleship placement

        :param player_id: current player id
        :type player_id: int
        :return: True/False
        """
        return self.__done_placement[player_id]

    def get_turn(self):
        """Returns the id of the player's who's turn is now

        :return: turn(int)
        """
        if not self.is_battleship_placement_done():
            raise GameControllerException("Battleship placement phase is not over")
        return self.__turn

    def mark_done_placement(self, player_id):
        """ Commits the placement for the current player

        :param player_id: player id for which the placement is committed
        :type player_id: int
        :return:
        """
        self.__validate_battleship_placement_player_id(player_id)
        if self.get_placed_battleships_count(player_id) != len(self._game_data.initial_battleships_sizes):
            raise GameControllerException("Not all battleships were placed")
        self.__done_placement[player_id] = True

    def get_grid_size(self):
        """Returns the game grid size

        :return: grid size(int)
        """
        return self._game_data.grid_size

    def get_player_live_battleships_count(self, player_id):
        """ Returns the number of battleships that have not yet been destroyed for the current player

        :param player_id: current player id
        :type player_id: int
        :return: count of "alive" battleships(int)
        """
        return sum(0 if battleship.destroyed else 1 for battleship in self._player_data[player_id].battleships_repository.list())

    def get_winner(self):
        """Gets the winner of the game

        :return: the player_id of the winner. If a winner isn't decided yet, it returns -1
        """
        if self.get_player_live_battleships_count(0) == 0:
            return 1
        if self.get_player_live_battleships_count(1) == 0:
            return 0
        return -1

    def get_last_move(self):
        """Gets the last performed move

        :return: move(Move)
        """
        return self.__last_move

    def get_last_move_destroyed_battleship_size(self):
        """Gets the battleship destroyed in the last move(if any)

        :return: size(int)
        """
        return self.__last_move_battleship_destroyed_size

    def reset_battleship(self, player_id, battleship_id):
        """ Resets a battleship so it becomes able to be placed again by the current player

        :param player_id: current player
        :type player_id: int
        :param battleship_id: battleship id
        :type battleship_id: int
        :return:
        """
        self.__validate_battleship_placement_player_id(player_id)
        battleship = self._player_data[player_id].battleships_repository.get_by_id(battleship_id)
        if battleship is None:
            raise GameControllerException("Battleship with specified id doesn't exist")
        battleship.placed = False
        self._player_data[player_id].battleships_repository.update(battleship_id, battleship)

    def get_player_battleship_masks(self, player_id):
        """ Returns the list containing the battleship masks for the given player

        :param player_id: player id of for which the masks should be retrieved
        :return: list of BattleshipMask
        """
        return self._player_data[player_id].opponent_mask_repository.list()
