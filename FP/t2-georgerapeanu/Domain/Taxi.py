from Domain.TaxiValidator import TaxiValidator


class Taxi:
    """ This class implements the Taxi object

    """
    def __init__(self, id, x, y, fare):
        """ Constructor for Taxi instance

        :param id: id of the taxi
        :type id: int
        :param x: first coordinate of the taxi
        :type x: int
        :param y: second coordinate of the taxi
        :type y: int
        :param fare: the fare of the taxi
        :type fare: int
        """
        self.__id = id
        TaxiValidator.validate_id(id)
        self.x = x
        self.y = y
        self.fare = fare

    @property
    def id(self):
        return self.__id

    @property
    def x(self):
        return self.__x

    @x.setter
    def x(self, value):
        TaxiValidator.validate_coord(value)
        self.__x = value

    @property
    def y(self):
        return self.__y

    @y.setter
    def y(self, value):
        TaxiValidator.validate_coord(value)
        self.__y = value

    @property
    def fare(self):
        return self.__fare

    @fare.setter
    def fare(self, value):
        TaxiValidator.validate_fare(value)
        self.__fare = value

    def __eq__(self, other):
        return  self.id == other.id and \
                self.x == other.x and \
                self.y == other.y and \
                self.fare == other.fare
