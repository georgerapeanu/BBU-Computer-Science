from Domain.DomainExceptions import MoveException
from Domain.IdValidator import IdValidator
from Domain.MoveStatus import MoveStatus


class MoveValidator(IdValidator):
    """Domain-validator for Move instances

    """

    @staticmethod
    def validate_coord(x):
        """ Checks that a coordinate is int
            Service should check if coordinates are possible

        :param x: x coordinate
        :type x: int
        :return:
        """
        if type(x) != int:
            raise MoveException("Battleship coordinates must be integers")

    @staticmethod
    def validate_player(player):
        """ Checks that a player is int
            Service should check if player exists

        :param player: player id
        :type player: int
        :return:
        """
        if type(player) != int:
            raise MoveException("Move player must be integers")

    @staticmethod
    def validate_status(status):
        """ Checks that a move status is valid

        :param status: status
        :type status: MoveStatus
        :return:
        """
        if not isinstance(status, MoveStatus):
            raise MoveException("Move status is invalid")
