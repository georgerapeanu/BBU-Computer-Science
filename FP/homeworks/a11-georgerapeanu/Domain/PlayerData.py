class PlayerData:
    def __init__(self, player_id, battleships_repository, moves_repository, opponent_mask_repository):
        """ Constructor for GameData object. This object is created only to pass information
            In a more scalable way

            :param player_id: the id of the current player(generally 0 or 1)
            :type player_id: int
            :param battleships_repository: the player's battleship repository
            :type battleships_repository: GeneralRepository
            :param moves_repository: the player's move repository
            :type moves_repository: GeneralRepository
            :param opponent_mask_repository: the player's battleship mask repository(i.e. his knowledge of the enemy)
            :type opponent_mask_repository: GeneralRepository
        """
        self.player_id = player_id
        self.battleships_repository = battleships_repository
        self.moves_repository = moves_repository
        self.opponent_mask_repository = opponent_mask_repository
