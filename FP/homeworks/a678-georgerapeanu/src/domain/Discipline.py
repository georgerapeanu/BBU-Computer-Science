from src.domain.DisciplineValidator import DisciplineValidator


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
        return "Discipline %d: %s" % (self.id, self.name)
