from Domain.DomainExceptions import IdValidatorException, TaxiValidatorException
from Domain.IdValidator import IdValidator


class TaxiValidator(IdValidator):
    @staticmethod
    def validate_coord(x):
        """ Checks that a coordinate is int
            Service should check if coordinates are possible

        :param x: x coordinate
        :type x: int
        :return:
        """
        if type(x) != int:
            raise TaxiValidatorException("Taxi coordinates should be ints")

    @staticmethod
    def validate_fare(fare):
        """ Checks that a fare is int

        :param fare: fare
        :type fare: int
        :return:
        """

        if type(fare) != int:
            raise TaxiValidatorException("Taxi fare should be int")
