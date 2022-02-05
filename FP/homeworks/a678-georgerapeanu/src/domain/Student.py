from src.domain.StudentValidator import StudentValidator


class Student:
    """This class implements Student

    """
    def __init__(self, student_id, name):
        StudentValidator.check_id(student_id)
        self.__id = student_id
        self.name = name

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        StudentValidator.check_name(name)
        self.__name = name

    def __eq__(self, other):
        return self.id == other.id and self.name == other.name

    def __str__(self):
        return "Student %d: %s" % (self.id, self.name)
