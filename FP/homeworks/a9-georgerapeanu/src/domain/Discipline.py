from src.domain.DisciplineValidator import DisciplineValidator
from src.domain.DomainExceptions import DisciplineException


class Discipline:
    """This class implements the Discipline class

    """
    def __init__(self, discipline_id, name):
        DisciplineValidator.check_id(discipline_id)
        self.__id = discipline_id
        self.name = name

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        DisciplineValidator.check_name(name)
        self.__name = name

    def __eq__(self, other):
        return self.id == other.id and self.name == other.name

    def __str__(self):
        return "Discipline #%d: %s" % (self.id, self.name)

    @classmethod
    def from_file_string(cls, s):
        id = None
        name = None
        try:
            fields = s.split(",")
            if len(fields) != 2:
                raise DisciplineException("String invalid")
            if len(fields[0]) == 0 or len(fields[1]) == 0:
                raise DisciplineException("String invalid")
            id = int(fields[0])
            name = fields[1]
        except Exception as ex:
            raise DisciplineException(str(ex))
        return Discipline(id, name)

    @classmethod
    def to_file_string(cls, discipline):
        return "%d,%s" % (discipline.id, discipline.name)
