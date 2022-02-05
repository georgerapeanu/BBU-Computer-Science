from Domain.BattleshipMask import BattleshipMask
from Domain.BattleshipOrientation import BattleshipOrientation
from Domain.BattleshipValidator import BattleshipValidator
from Domain.DomainExceptions import BattleshipException, IdValidatorException


class Battleship(BattleshipMask):
    """ This class implements Battleship

    """

    def __init__(self, id, size, destroyed, x, y, orientation, placed):
        """Constructor for Battleship instance

        :param id: id
        :type id: int
        :param size:size of battleship
        :type size: int
        :param x: x coordinate of battleship
        :type x: int
        :param y: y coordinate of battleship
        :type y: int
        :param orientation: battleship's orientation
        :type orientation: BattleshipOrientation
        :param placed: true if battleship is placed(i.e. has its final coordinates) false otherwise
        :type placed: bool
        """
        super().__init__(id, size, destroyed)
        self.x = x
        self.y = y
        self.orientation = orientation
        self.placed = placed

    @property
    def placed(self):
        return self.__placed

    @placed.setter
    def placed(self, value):
        BattleshipValidator.validate_placed(value)
        self.__placed = value

    @property
    def x(self):
        return self.__x

    @x.setter
    def x(self, value):
        BattleshipValidator.validate_coord(value)
        self.__x = value

    @property
    def y(self):
        return self.__y

    @y.setter
    def y(self, value):
        BattleshipValidator.validate_coord(value)
        self.__y = value

    @property
    def orientation(self):
        return self.__orientation

    @orientation.setter
    def orientation(self, value):
        BattleshipValidator.validate_orientation(value)
        self.__orientation = value

    def get_bounding_box(self):
        """Returns the bounding box of the battleship

        :return: list containing [x_min, y_min, x_max, y_max]
        """

        ans = [self.x, self.y, self.x, self.y]

        if self.orientation == BattleshipOrientation.VERTICAL:
            ans[2] += self.size - 1
        else:
            ans[3] += self.size - 1

        return ans

    def __eq__(self, other):
        """ Equality operator

        :param other: other instance
        :type other: Battleship
        :return:
        """
        return self.id == other.id and \
               self.size == other.size and \
               self.placed == other.placed and \
               self.x == other.x and \
               self.y == other.y and \
               self.destroyed == other.destroyed and \
               self.orientation == other.orientation
