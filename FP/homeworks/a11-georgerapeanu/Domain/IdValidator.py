from Domain.DomainExceptions import IdValidatorException


class IdValidator:
    @staticmethod
    def validate_id(id):
        """ Checks that id is positive integer

        :param id: id to be checked
        :type id: int
        :return:
        """

        if type(id) != int:
            raise IdValidatorException("id should be an integer")

        if id < 0:
            raise IdValidatorException("id should be positive")
