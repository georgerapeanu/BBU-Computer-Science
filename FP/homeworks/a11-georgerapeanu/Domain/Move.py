from Domain.DomainExceptions import IdValidatorException, MoveException
from Domain.MoveValidator import MoveValidator


class Move:
    """ This class implements Move

    """
    def __init__(self, id, player, x, y, status):
        """ Constructor for Move instance

        :param id: id
        :type id: int
        :param player: player id
        :type player: int
        :param x: x
        :type x: int
        :param y: y
        :type y: int
        :param status: status
        :type status: MoveStatus
        """
        try:
            MoveValidator.validate_id(id)
        except IdValidatorException as ex:
            raise MoveException("Move's " + str(ex))
        self.__id = id
        self.player = player
        self.x = x
        self.y = y
        self.status = status

    @property
    def id(self):
        return self.__id

    @property
    def player(self):
        return self.__player

    @player.setter
    def player(self, value):
        MoveValidator.validate_player(value)
        self.__player = value

    @property
    def x(self):
        return self.__x

    @x.setter
    def x(self, value):
        MoveValidator.validate_coord(value)
        self.__x = value

    @property
    def y(self):
        return self.__y

    @y.setter
    def y(self, value):
        MoveValidator.validate_coord(value)
        self.__y = value

    @property
    def status(self):
        return self.__status

    @status.setter
    def status(self, value):
        MoveValidator.validate_status(value)
        self.__status = value

    def __eq__(self, other):
        """ Equality operator

        :param other: other move
        :type other: Move
        :return:
        """
        return self.id == other.id and \
               self.player == other.player and\
               self.x == other.x and \
               self.y == other.y and \
               self.status == other.status
