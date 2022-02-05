from Domain.Exceptions import IdObjectException


class IdObjectValidator:
    """ Validates a given id

    """
    @staticmethod
    def validate_id(id):
        """ Checks that given id is valid. For this, it should be a positive integer.
            Raises IdObjectException if invalid

        :param id: the id to be checked
        :type id: int
        :return:
        """

        if type(id) != int:
            raise IdObjectException("Id is not an integer")
        if id < 0:
            raise IdObjectException("Id is not positive")
    