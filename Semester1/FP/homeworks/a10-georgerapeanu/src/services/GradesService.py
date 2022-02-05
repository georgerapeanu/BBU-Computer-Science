from src.domain.ActionComposite import ActionComposite
from src.domain.ActionLeaf import ActionLeaf
from src.domain.UndoAction import UndoAction
from src.services.ServiceExceptions import GradesServiceException
from src.domain.Grade import Grade
from src.repository.GeneralRepository import GeneralRepository
from src.repository.UndoRepository import UndoRepository
from src.utils import utils


class GradesService:
    def __init__(self, grade_repository, student_repository, discipline_repository, undo_repository):
        """ Constructor for GradeService

        :param grade_repository: the grade repository
        :type grade_repository: GeneralRepository
        :param student_repository: the student repository
        :type student_repository: GeneralRepository
        :param discipline_repository: the discipline repository
        :type discipline_repository: GeneralRepository
        :param undo_repository: the undo repository
        :type undo_repository: UndoRepository
        """
        self.__grade_repository = grade_repository
        self.__student_repository = student_repository
        self.__discipline_repository = discipline_repository
        self.__undo_repository = undo_repository

    def __get_free_id(self):
        tmp = utils.Utils.sort(self.__grade_repository.list(), lambda a, b: a.id < b.id)
        for i in range(0, len(tmp)):
            if tmp[i].id != i + 1:
                return i + 1
        return len(tmp) + 1

    def add_grade(self, student_id, discipline_id, grade):
        """ This method adds a grade to the repository

        :param student_id: the id of the student
        :type student_id: int
        :param discipline_id: the id of the discipline
        :type discipline_id: int
        :param grade: the value of the grade
        :type grade: int
        :return:
        """
        _grade = Grade(self.__get_free_id(), student_id, discipline_id, grade)
        if self.__student_repository.get_by_id(student_id) is None:
            raise GradesServiceException("student with specified id doesn't exist")
        if self.__discipline_repository.get_by_id(discipline_id) is None:
            raise GradesServiceException("discipline with specified id doesn't exist")
        self.__grade_repository.add(_grade)
        undo_action = ActionLeaf(self.__grade_repository.delete, tuple([_grade.id]))
        redo_action = ActionLeaf(self.__grade_repository.add, tuple([_grade]))
        action = UndoAction(undo_action, redo_action)
        self.__undo_repository.add(action)

    def delete_student(self, student_id):
        """ This function deletes a student by id and all its corresponding grades

        :param student_id: student id
        :type student_id: int
        :return: None
        """

        student = self.__student_repository.get_by_id(student_id)
        if student is None:
            raise GradesServiceException("student with specified id doesn't exist")
        grades = utils.Utils.filter(self.__grade_repository.list(), lambda x: x.student_id == student_id)

        redo_action = ActionComposite()
        undo_action = ActionComposite()

        self.__student_repository.delete(student.id)
        undo_action.add(ActionLeaf(self.__student_repository.add, tuple([student])))
        for grade in grades:
            redo_action.add(ActionLeaf(self.__grade_repository.delete, tuple([grade.id])))
            undo_action.add(ActionLeaf(self.__grade_repository.add, tuple([grade])))
            self.__grade_repository.delete(grade.id)

        redo_action.add(ActionLeaf(self.__student_repository.delete, tuple([student.id])))
        action = UndoAction(undo_action, redo_action)
        self.__undo_repository.add(action)

    def delete_discipline(self, discipline_id):
        """ This function deletes a discipline by id and all its corresponding grades

        :param discipline_id: discipline id
        :type discipline_id: int
        :return: None
        """

        discipline = self.__discipline_repository.get_by_id(discipline_id)
        if discipline is None:
            raise GradesServiceException("discipline with specified id doesn't exist")
        grades = utils.Utils.filter(self.__grade_repository.list(), lambda x: x.discipline_id == discipline_id)

        redo_action = ActionComposite()
        undo_action = ActionComposite()

        self.__discipline_repository.delete(discipline.id)
        undo_action.add(ActionLeaf(self.__discipline_repository.add, tuple([discipline])))
        for grade in grades:
            redo_action.add(ActionLeaf(self.__grade_repository.delete, tuple([grade.id])))
            undo_action.add(ActionLeaf(self.__grade_repository.add, tuple([grade])))
            self.__grade_repository.delete(grade.id)

        redo_action.add(ActionLeaf(self.__discipline_repository.delete, tuple([discipline.id])))
        action = UndoAction(undo_action, redo_action)
        self.__undo_repository.add(action)

    def list(self):
        """ Lists all grades

        :return: list of grades
        """
        return self.__grade_repository.list()
