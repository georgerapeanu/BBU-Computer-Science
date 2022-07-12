from Domain.BattleshipOrientation import BattleshipOrientation
from Domain.DomainExceptions import BattleshipException
from Domain.IdValidator import IdValidator


class BattleshipValidator(IdValidator):
    """Domain-validator for Battleship instances

    """

    @staticmethod
    def validate_size(size):
        """ Raises BattleshipException if the size is not a positive integer
            Service should check that it's size is possible

        :param size: the size to be validated
        :type size: int
        :return:
        """
        if type(size) != int:
            raise BattleshipException("Battleship size must be an integer")

        if size <= 0:
            raise BattleshipException("Battleship size must be strictly positive")

    @staticmethod
    def validate_coord(x):
        """ Checks that a coordinate is int
            Service should check if coordinates are possible

        :param x: x coordinate
        :type x: int
        :return:
        """
        if type(x) != int:
            raise BattleshipException("Battleship coordinates must be integers")

    @staticmethod
    def validate_orientation(orientation):
        """ Checks that orientation is valid

        :param orientation: orientation
        :type orientation: BattleshipOrientation
        :return:
        """

        if not isinstance(orientation, BattleshipOrientation):
            raise BattleshipException("Battleship's orientation is invalid")

    @staticmethod
    def validate_placed(value):
        """ Checks that value is bool

        :param value: value
        :type value: bool
        :return:
        """

        if type(value) != bool:
            raise BattleshipException("placed value invalid")

    @staticmethod
    def validate_destroyed(value):
        """ Checks that value is bool

        :param value: value
        :type value: bool
        :return:
        """

        if type(value) != bool:
            raise BattleshipException("destroyed value invalid")
