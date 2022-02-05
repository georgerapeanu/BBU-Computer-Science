from Domain.IdObjectValidator import IdObjectValidator


class IdObject:
    """Base class for any object that uses id's

    """
    def __init__(self, id):
        IdObjectValidator.validate_id(id)
        self.__id = id

    @property
    def id(self):
        return self.__id