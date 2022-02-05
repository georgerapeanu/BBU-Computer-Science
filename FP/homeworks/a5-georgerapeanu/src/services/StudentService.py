from src.repository.Repository import Repository
from src.domain.Student import Student


class StudentService:
    def __init__(self, n = 0):
        """This is the constructor for the StudentService

        :param n: the number of initial students(default value 0)
        :type n: int
        """
        self.__repository = Repository(n)

    def add_student(self, id, name, group):
        """This function adds a student to the current repository

        :param id: id of the student
        :type id: int
        :param name: name of the student
        :type name: string
        :param group: group of the student
        :type group: int
        :return: None
        """
        self.__repository.add_student(Student(id, name, group))

    def get_students(self):
        """This function returns the current students

        :return: list of students
        """
        return self.__repository.get_students()

    def filter(self, group):
        """This function filters the repo, deleting all students that are from specified group

        :param group: group
        :type group: int
        :return: None
        """
        self.__repository.filter(lambda x: x.group != group)

    def undo(self):
        """This function undoes the last operation that modified the repository

        :return: None
        """
        self.__repository.undo()