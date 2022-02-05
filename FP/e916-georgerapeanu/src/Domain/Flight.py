from src.Domain.Exceptions import FlightException
from src.Domain.FlightValidator import FlightValidator
from src.Domain.IdObject import IdObject


class Flight(IdObject):
    """ This class implements the model that is used to represent a flight

    """

    def __init__(self, id, departure_city, departure_time, arrival_city, arrival_time):
        """ Constructor for an flight object.

        :param id: the id of the object(in this case the flight identifier is used)
        :type id: string
        :param departure_city: the city from which the flight departs
        :type departure_city: str
        :param departure_time: the time at which the flight departs(it is stored as hours * 60 + minute)
        :type departure_time: int
        :param arrival_city: the city to which the flight arrives.
        :type arrival_city: str
        :param arrival_time: the time at which the flight arrives(it is also stored as hours * 60 + minute)
        :type arrival_time: int
        """

        FlightValidator.validate_id(id)
        super().__init__(id)
        self.departure_city = departure_city
        self.departure_time = departure_time
        self.arrival_city = arrival_city
        self.arrival_time = arrival_time

    @property
    def departure_city(self):
        """ Getter for departure city property

        :return: string
        """
        return self.__departure_city

    @departure_city.setter
    def departure_city(self, value):
        """ Setter for departure city property

        :param value: the departure city
        :type value: str
        :return: None
        """
        FlightValidator.validate_city(value)
        self.__departure_city = value

    @property
    def arrival_city(self):
        """ Getter for the arrival city property

        :return: string
        """
        return self.__arrival_city

    @arrival_city.setter
    def arrival_city(self, value):
        """ Setter for the arrival city property

        :param value: the arrival city
        :type value: str
        :return: None
        """
        FlightValidator.validate_city(value)
        self.__arrival_city = value

    @property
    def arrival_time(self):
        """ Getter for the arrival time property

        :return: int
        """
        return self.__arrival_time

    @arrival_time.setter
    def arrival_time(self, value):
        """ Setter for the arrival time property

        :param value: the arrival time
        :type value: int
        :return:
        """
        FlightValidator.validate_time(value)
        self.__arrival_time = value

    @property
    def departure_time(self):
        """ Getter for the departure time property

        :return: int
        """
        return self.__departure_time

    @departure_time.setter
    def departure_time(self, value):
        """ Setter for the departure time property

        :param value: the departure time
        :type value: int
        :return: None
        """
        FlightValidator.validate_time(value)
        self.__departure_time = value

    def __str__(self):
        """ This converts a Flight object to string.

        :return: str
        """

        (departure_hour, departure_minute) = (self.departure_time // 60, self.departure_time % 60)
        (arrival_hour, arrival_minute) = (self.arrival_time // 60, self.arrival_time % 60)

        return "%s,%s,%.2d:%.2d,%s,%.2d:%.2d" % (self.id, self.departure_city, departure_hour, departure_minute,
                                                 self.arrival_city, arrival_hour, arrival_minute)

    @staticmethod
    def init_from_string(s):
        """ This static method creates a Flight object from a string. Raises FlightException if string is invalid
        :param s: the string
        :type s: str
        :return: Flight
        """

        FlightValidator.validate_string(s)
        try:
            args = s.split(",")
            for i in range(0, len(args)):
                args[i] = args[i].strip()

            id = args[0].strip()
            departure_city = args[1].strip()
            arrival_city = args[3].strip()

            departure_hour = int(args[2].split(":")[0].strip())
            departure_minute = int(args[2].split(":")[1].strip())

            arrival_hour = int(args[4].split(":")[0].strip())
            arrival_minute = int(args[4].split(":")[1].strip())

            departure_time = departure_hour * 60 + departure_minute
            arrival_time = arrival_hour * 60 + arrival_minute

            return Flight(id, departure_city, departure_time, arrival_city, arrival_time)
        except Exception as ex:
            raise Exception("invalid string")

    def __eq__(self, other):
        """ Equality operator

        :param other: the other flight
        :type other: Flight
        :return: boolean(True if equal False otherwise)
        """

        return  self.id == other. id and self.departure_city == other.departure_city and \
                self.arrival_city == other.arrival_city and self.arrival_time == other.arrival_time and \
                self.departure_time == other.departure_time
