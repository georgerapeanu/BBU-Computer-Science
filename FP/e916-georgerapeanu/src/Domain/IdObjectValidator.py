from src.Domain.Exceptions import IdObjectException


class IdObjectValidator:
    """ Class used for validating IdObjects

    """
    @staticmethod
    def validate_id(id):
        """ Validates that a given id is suitable(it is a string or an int).
            Raises IdObjectException if this is not true

        :param id: the id
        :type id: int|str
        :return: None
        """

        if type(id) != str and type(id) != int:
            raise IdObjectException("Id should be int or string")
