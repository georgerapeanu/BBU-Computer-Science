from Domain.GameData import GameData
from Service.GenericPlayer import GenericPlayer


class ModelAI(GenericPlayer):
    """Generic model for all AI classes

    """

    def __init__(self, player_data, game_data):
        """ Constructor for an ModelAI

        :param player_data: described in GenericPlayer
        :param game_data: the game data
        :type game_data: GameData
        """
        super().__init__(player_data)
        self._game_data = game_data

    def place_battleships(self):
        """ This method should implement the algorithm that the AI uses in order to place its initial battleships
            The app assumes that the AI does not make any invalid moves.
            This method should just update the uninitialised battleships in its repository
        :return:
        """
        pass

    def get_best_move(self):
        """ This method should just return a valid next move for the state that the AI is in
        :return:
        """
        pass

    def notify_last_move_destroyed_ship(self, size):
        """ Called to notify the ai that his last move actually destroyed a ship

        :param size: the size of the destrored ship or None if last move didn't destroy anything
        :type size: int|None
        :return:
        """