from Domain.RideValidator import RideValidator


class Ride:
    """ This class implements the Ride object

    """

    def __init__(self, start, end):
        """

        :param start: tuple containing the coordinates of the start of the ride
        :type start: tuple
        :param end: tuple containing the coordinates of the end of the ride
        :type end: tuple
        """

        self.start = start
        self.end = end

    @property
    def start(self):
        return self.__start

    @start.setter
    def start(self, value):
        RideValidator.validate_point(value)
        self.__start = value

    @property
    def end(self):
        return self.__end

    @end.setter
    def end(self, value):
        RideValidator.validate_point(value)
        self.__end = value
