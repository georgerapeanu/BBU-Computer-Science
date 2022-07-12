from src.Domain.Exceptions import FlightException


class FlightValidator:
    """ Class used to validate flights

    """
    @staticmethod
    def validate_city(city):
        """ Validates that a city is a string
            Raises FlightException otherwise

        :param city: the city to be validated
        :type city: str
        :return: None
        """
        if type(city) != str:
            raise FlightException("The city should be a string")

    @staticmethod
    def validate_time(time):
        """ Validates that a certain time is an int and that is in the admissible interval
            (i.e. in the interval [0, 23 * 60 + 59])
            Raises FlightException otherwise

        :param time: the time to be validated
        :type time: int
        :return: None
        """

        if type(time) != int:
            raise FlightException("The time should be an integer")
        if time < 0 or time > 23 * 60 + 59:
            raise FlightException("Time is invalid")

    @staticmethod
    def validate_string(s):
        """ Validates that a certain s is a string.

        Raises flight exception if not

        :param s: the string
        :type s: str
        :return: None
        """

        if type(s) != str:
            raise FlightException("String is invalid")

    @staticmethod
    def validate_id(id):
        """ Valdiates that given string is id
            Raises FlightException otherwise

        :param id: the id
        :type id: str
        :return: None
        """

        if type(id) != str:
            raise FlightException("Flight id should be string")
