from Domain.PlayerData import PlayerData


class GenericPlayer:

    """This is a model for what a player instance should be able to do

    """

    def __init__(self, player_data):
        """

        :param player_data: the player data
        :type player_data: PlayerData
        """
        self._player_data = player_data

    def get_battleships(self):
        """Gets the battleships of the current player

        :return: list of battleships
        """
        return self._player_data.battleships_repository.list()

    def get_moves(self):
        """ Gets the moves of the current player

        :return: list of moves
        """
        return self._player_data.moves_repository.list()

    def get_player_id(self):
        """ Gets the player id

        :return: player id(int)
        """
        return self._player_data.player_id
