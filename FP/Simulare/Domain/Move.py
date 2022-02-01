from Domain.IdObject import IdObject
from Domain.MoveValidator import MoveValidator


class Move(IdObject):
    """ This is the class which models how a move should look like.
        Due to the nature of the game, the turn can be determined by the parity of the number of moves
        And committed moves are the for both Order or Chaos
        So, remembering the player which committed the move is redundant

    """
    def __init__(self, id, x, y, value):
        super().__init__(id)
        self.x = x
        self.y = y
        self.value = value

    @property
    def x(self):
        return self.__x

    @x.setter
    def x(self, value):
        MoveValidator.validate_coordinate(value)
        self.__x = value

    @property
    def y(self):
        return self.__y

    @y.setter
    def y(self, value):
        MoveValidator.validate_coordinate(value)
        self.__y = value

    @property
    def value(self):
        return self.__value

    @value.setter
    def value(self, value):
        MoveValidator.validate_value(value)
        self.__value = value

    def __eq__(self, other):
        return  self.id == other.id and \
                self.x == other.x and \
                self.y == other.y and \
                self.value == other.value

    def __str__(self):
        """ This is used for transforming the object to a string mainly for storage

        :return: string
        """
        return "Move #%d %d %d %s" % (self.id, self.x, self.y, self.value)

    @staticmethod
    def init_from_string(s):
        """ This should be called in order to get a Move object from a string

        :param s: the string from which to get the move
        :type s: str
        :return: Move
        """
        MoveValidator.validate_string(s)
        move = Move(int(s.split(" ")[1].split("#")[1]), int(s.split(" ")[2]), int(s.split(" ")[3]), s.split(" ")[4].strip())
        return move
