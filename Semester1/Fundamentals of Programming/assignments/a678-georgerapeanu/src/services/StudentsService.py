from src.domain.ActionLeaf import ActionLeaf
from src.domain.UndoAction import UndoAction
from src.services.ServiceExceptions import StudentsServiceException
from src.domain.Student import Student
from src.repository.GeneralRepository import GeneralRepository
from src.repository.UndoRepository import UndoRepository


class StudentsService:
    def __init__(self, student_repository,  undo_repository):
        """ Constructor for StudentsService

        :param student_repository: student repository
        :type student_repository: GeneralRepository
        :param undo_repository: undo repository
        :type undo_repository: UndoRepository
        """
        self.__repository = student_repository
        self.__undo_repository = undo_repository

    def add_student(self, id, name):
        """ This method adds the student with the specified id and name

        :param id: id of student
        :type id: int
        :param name: name of student
        :type name: string
        :return: None
        """
        student = Student(id, name)
        self.__repository.add(student)
        undo_action = ActionLeaf(self.__repository.delete, tuple([student.id]))
        redo_action = ActionLeaf(self.__repository.add, tuple([student]))
        action = UndoAction(undo_action, redo_action)
        self.__undo_repository.add(action)

    def update_student(self, id, name):
        """ This method updates the student with the specified id

        :param id: id of student
        :type id: int
        :param name: name of student
        :type name: string
        :return: None
        """

        student = self.__repository.get_by_id(id)
        if student is None:
            raise StudentsServiceException("cannot update student with specified id")
        self.__repository.update(id, Student(id, name))
        undo_action = ActionLeaf(self.__repository.update, tuple([id, student]))
        redo_action = ActionLeaf(self.__repository.update, tuple([id, Student(id, name)]))
        action = UndoAction(undo_action, redo_action)
        self.__undo_repository.add(action)

    def get_by_id(self, id):
        """ This method returns the student with specified id or None if it doesn't exist

        :param id: the specified id
        :type id: int
        :return: list of disciplines
        """
        return self.__repository.get_by_id(id)

    def list_by_name(self, name):
        """ This method returns a list of all students that match given name

        :param name: the given name
        :type name: string
        :return: list of disciplines
        """
        return list(filter(lambda x: x.name.lower().find(name.lower()) != -1, self.__repository.list()))

    def list(self):
        """ This method returns a list of all students

        :return: list of students
        """
        return self.__repository.list()
