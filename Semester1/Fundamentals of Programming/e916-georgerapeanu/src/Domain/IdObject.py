from src.Domain.IdObjectValidator import IdObjectValidator


class IdObject:
    """ This class implements the model used by all classes which have an id

    """

    def __init__(self, id):
        """ The constructor for an IdObject class

        :param id: the id that is used to identify the object
        :type id: int|str
        """
        IdObjectValidator.validate_id(id)
        self.__id = id

    @property
    def id(self):
        """ Getter for id property

        :return: int|string(the id)
        """
        return self.__id
