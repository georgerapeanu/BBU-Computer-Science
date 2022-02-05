class GameData:
    def __init__(self, grid_size, initial_boat_sizes):
        """ Constructor for GameData object. This object is created only to pass information
        In a more scalable way

        :param grid_size: the grid size
        :type grid_size: int
        :param initial_boat_sizes: list of initial battleship sizes
        :type initial_boat_sizes: list
        """
        self.grid_size = grid_size
        self.initial_battleships_sizes = initial_boat_sizes
