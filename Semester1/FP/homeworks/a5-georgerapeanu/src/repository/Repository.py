from copy import deepcopy
from random import Random
import names
from src.domain.Student import Student


class RepositoryException(Exception):
    pass


class Repository:
    """This class implements the repository for our application

    """
    def __init__(self, n = 0):
        """This constructor initializes a student repository

        :param n: number of initial students(default value 0)
        :type n: int
        """
        self.__students = {}
        self.__history = []

        rng = Random(23)

        for i in range(0, n):
            id = i + 1
            name = names.get_first_name()
            group = rng.randint(1, 10)
            self.__students[id] = Student(id, name, group)

    def add_student(self, student):
        """This function adds a student to the repository

        raises RepositoryException if id is already in use

        :param student: student to be added
        :type student: Student
        :return: None
        """
        if student.id in self.__students:
            raise RepositoryException("Student id is already taken")
        self.__history.append(deepcopy(self.__students))
        self.__students[student.id] = student

    def get_students(self):
        """This function returns a list of the current students

        :return: list of students
        """

        student_list = []

        for student in self.__students.values():
            student_list.append(student)

        return student_list

    def filter(self, filter_function):
        """This function filters the current student dictionary using a filter function

        :param filter_function: the function with which to filter the students
        :return: None
        """
        self.__history.append(deepcopy(self.__students))
        new_students = {}
        for x in self.__students.values():
            if filter_function(x):
                new_students[x.id] = x
        self.__students = new_students

    def undo(self):
        """This function undoes the last operation which modified the internal structure
        raises RepositoryException if there is nothing to be undone

        :return: None
        """
        if len(self.__history) == 0:
            raise RepositoryException("Cannot undo any further")
        self.__students = self.__history[-1]
        self.__history.pop()
