from src.domain.StudentValidator import StudentValidator


class Student:
    """This class implements the model for the Student entity
    """
    def __init__(self, id, name, group):
        """This constructor takes as arguments an id, name, and a group

        :param id: unique positive integer
        :type id: int
        :param name: name of the student
        :type name: string
        :param group: group of the student
        :type group: int

        :return: None
        """
        StudentValidator.check_id(id)
        self.__id = id
        self.name = name
        self.group = group

    def __str__(self):
        return str(self.id) + ". " + self.name + " " + str(self.group)

    def __eq__(self, other):
        return self.id == other.id and \
               self.name == other.name and \
               self.group == other.group


    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        name = name.strip()
        StudentValidator.check_name(name)
        self.__name = name

    @property
    def group(self):
        return self.__group

    @group.setter
    def group(self, group):
        StudentValidator.check_group(group)
        self.__group = group
