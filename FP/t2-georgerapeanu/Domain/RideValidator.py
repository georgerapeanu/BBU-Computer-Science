from Domain.DomainExceptions import IdValidatorException, TaxiValidatorException, RideValidatorException
from Domain.IdValidator import IdValidator


class RideValidator(IdValidator):
    @staticmethod
    def validate_point(v):
        """ Checks that a tuple is valid to be interpreted as coordinates
            Service should check if coordinates are possible

        :param v: v coordinate
        :type v: tuple
        :return:
        """

        if type(v) != tuple:
            raise RideValidatorException("Start/end should be tuples")

        if len(v) != 2:
            raise RideValidatorException("Start/end should be tuples of 2 elements")

        if type(v[0]) != int or type(v[1]) != int:
            raise RideValidatorException("Start/end should be tuples of 2 integers")
