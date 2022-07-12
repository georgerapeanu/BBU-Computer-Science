from Domain.BattleshipValidator import BattleshipValidator
from Domain.DomainExceptions import IdValidatorException, BattleshipException


class BattleshipMask:
    """This class contains only the data that the opponent is able to know

    """

    def __init__(self, id, size, destroyed):
        """Constructor for BattleshipMask

        :param id: id
        :type id: int
        :param size: size
        :type size: int
        :param destroyed: True if battleship is destroyed False otherwise
        :type destroyed: boolean
        """
        try:
            BattleshipValidator.validate_id(id)
        except IdValidatorException as ex:
            raise BattleshipException("Battleship's " + str(ex))
        self.__id = id
        self.size = size
        self.destroyed = destroyed

    @property
    def id(self):
        return self.__id

    @property
    def size(self):
        return self.__size

    @size.setter
    def size(self, value):
        BattleshipValidator.validate_size(value)
        self.__size = value

    @property
    def destroyed(self):
        return self.__destroyed

    @destroyed.setter
    def destroyed(self, value):
        BattleshipValidator.validate_destroyed(value)
        self.__destroyed = value

    def __eq__(self, other):
        """ Equality operator

        :param other: other battleship mask
        :type other: BattleshipMask
        :return:
        """
        return self.id == other.id and \
               self.size == other.size and \
               self.destroyed == other.destroyed
