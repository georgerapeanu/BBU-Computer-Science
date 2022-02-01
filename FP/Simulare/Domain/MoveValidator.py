import re

from Domain.Exceptions import MoveException
from Domain.IdObjectValidator import IdObjectValidator


class MoveValidator(IdObjectValidator):
    """ This class is responsible for validating move data
        It only checks that the type is int for coordinates and that the placed object on the board is either X or O
    """

    @staticmethod
    def validate_coordinate(x):
        """ This validates a coordinate. If it is not an integer raises MoveException

        :param x: the coordinate to be validated
        :type x: int
        :return:
        """

        if type(x) != int:
            raise MoveException("Move coordinate is not an int")

    @staticmethod
    def validate_value(value):
        """ It checks that the value is a string, either 'X' or 'O'
            Raises MoveException if not
        :param value: the value to be checked
        :type value: str
        :return:
        """

        if value not in ['X', 'O']:
            raise MoveException("Move value is invalid")

    @staticmethod
    def validate_string(s):
        """ Checks if the given string has the correct format(and that it is a string).
            Raises MoveException if not

        :param s: the string to be tested
        :return:
        """

        if type(s) != str:
            raise MoveException("Tried to load from nonstring")

        if re.match("^Move #[0-9]+ [0-9]+ [0-9]+ [XO]$", s) is None:
            raise MoveException("Move string invalid")
