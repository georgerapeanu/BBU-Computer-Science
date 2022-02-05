import unittest

from src.domain.Discipline import Discipline
from src.domain.Grade import Grade
from src.domain.Student import Student
from src.repository.GeneralRepository import GeneralRepository
from src.repository.RepositoryExceptions import UndoRepositoryException
from src.repository.UndoRepository import UndoRepository
from src.services.DisciplinesService import DisciplinesService
from src.services.GradesService import GradesService
from src.services.ServiceExceptions import StudentsServiceException, DisciplinesServiceException, GradesServiceException
from src.services.StudentsService import StudentsService
from src.services.UndoService import UndoService
from src.services.StatisticsService import StatisticsService


class StudentsServiceTests(unittest.TestCase):
    def setUp(self):
        self.students_service = StudentsService(GeneralRepository(), UndoRepository())
        self.students_service.add_student(1, "aaa")
        self.students_service.add_student(3, "bbBb")

    def test_add(self):
        self.assertEqual(self.students_service.list(), [Student(1, "aaa"), Student(3, "bbBb")])

    def test_update(self):
        self.students_service.update_student(1, "b")
        self.assertEqual(self.students_service.list(), [Student(1, "b"), Student(3, "bbBb")])

    def test_list_by_id(self):
        self.assertEqual(self.students_service.get_by_id(1), Student(1, "aaa"))
        self.assertEqual(self.students_service.get_by_id(2), None)

    def test_list_by_name(self):
        self.assertEqual(self.students_service.list_by_name("A"), [Student(1, "aaa")])
        self.assertEqual(self.students_service.list_by_name("AAAA"), [])
        self.assertEqual(self.students_service.list_by_name("ab"), [])
        self.assertEqual(self.students_service.list_by_name("bBbb"), [Student(3, "bbBb")])

    def test_raises(self):
        with self.assertRaises(StudentsServiceException):
            self.students_service.update_student(2, "nu exist")


class DisciplinesServiceTests(unittest.TestCase):
    def setUp(self):
        self.disciplines_service = DisciplinesService(GeneralRepository(), UndoRepository())
        self.disciplines_service.add_discipline(1, "aaa")
        self.disciplines_service.add_discipline(3, "bbBb")

    def test_add(self):
        self.assertEqual(self.disciplines_service.list(), [Discipline(1, "aaa"), Discipline(3, "bbBb")])

    def test_update(self):
        self.disciplines_service.update_discipline(1, "b")
        self.assertEqual(self.disciplines_service.list(), [Discipline(1, "b"), Discipline(3, "bbBb")])

    def test_list_by_id(self):
        self.assertEqual(self.disciplines_service.get_by_id(1), Discipline(1, "aaa"))
        self.assertEqual(self.disciplines_service.get_by_id(2), None)

    def test_list_by_name(self):
        self.assertEqual(self.disciplines_service.list_by_name("A"), [Discipline(1, "aaa")])
        self.assertEqual(self.disciplines_service.list_by_name("AAAA"), [])
        self.assertEqual(self.disciplines_service.list_by_name("ab"), [])
        self.assertEqual(self.disciplines_service.list_by_name("bBbb"), [Discipline(3, "bbBb")])

    def test_raises(self):
        with self.assertRaises(DisciplinesServiceException):
            self.disciplines_service.update_discipline(2, "nu exist")


class GradesServiceTests(unittest.TestCase):
    def setUp(self):
        grade_repository = GeneralRepository()
        student_repository = GeneralRepository()
        discipline_repository = GeneralRepository()
        undo_repository = UndoRepository()
        
        self.students_service = StudentsService(student_repository, undo_repository)
        self.disciplines_service = DisciplinesService(discipline_repository, undo_repository)
        self.grades_service = GradesService(grade_repository, student_repository, discipline_repository, undo_repository)

        self.students_service.add_student(1, "Cineva")
        self.students_service.add_student(2, "Tu")
        self.students_service.add_student(3, "Altcineva")
        self.students_service.add_student(4, "idk")

        self.disciplines_service.add_discipline(1, "FP")
        self.disciplines_service.add_discipline(2, "CSA")
        self.disciplines_service.add_discipline(5, "Scoala vietii")

        self.grades_service.add_grade(1, 5, 10)
        self.grades_service.add_grade(3, 5, 1)
        self.grades_service.add_grade(1, 2, 4)
        self.grades_service.add_grade(2, 1, 10)
        self.grades_service.add_grade(2, 1, 0)
        self.grades_service.add_grade(3, 1, 0)
        self.grades_service.add_grade(4, 1, 10)
        self.grades_service.add_grade(4, 1, 10)
        self.grades_service.add_grade(4, 2, 1)

    def test_add_grade(self):
        self.assertEqual(self.grades_service.list(), [Grade(1, 1, 5, 10),
                                                      Grade(2, 3, 5, 1),
                                                      Grade(3, 1, 2, 4),
                                                      Grade(4, 2, 1, 10),
                                                      Grade(5, 2, 1, 0),
                                                      Grade(6, 3, 1, 0),
                                                      Grade(7, 4, 1, 10),
                                                      Grade(8, 4, 1, 10),
                                                      Grade(9, 4, 2, 1)])

    def test_raises(self):
        with self.assertRaises(GradesServiceException):
            self.grades_service.add_grade(6, 1, 10)

        with self.assertRaises(GradesServiceException):
            self.grades_service.add_grade(1, 10, 10)

    def test_delete_discipline(self):
        with self.assertRaises(GradesServiceException):
            self.grades_service.delete_discipline(10)
        self.grades_service.delete_discipline(1)
        self.assertEqual(self.grades_service.list(), [Grade(1, 1, 5, 10),
                                                      Grade(2, 3, 5, 1),
                                                      Grade(3, 1, 2, 4),
                                                      Grade(9, 4, 2, 1)])
        self.grades_service.add_grade(3, 5, 2)
        self.assertEqual(self.grades_service.list(), [Grade(1, 1, 5, 10),
                                                      Grade(2, 3, 5, 1),
                                                      Grade(3, 1, 2, 4),
                                                      Grade(9, 4, 2, 1),
                                                      Grade(4, 3, 5, 2)])

    def test_delete_student(self):
        with self.assertRaises(GradesServiceException):
            self.grades_service.delete_student(10)
        self.grades_service.delete_student(1)
        self.assertEqual(self.grades_service.list(), [Grade(2, 3, 5, 1),
                                                      Grade(4, 2, 1, 10),
                                                      Grade(5, 2, 1, 0),
                                                      Grade(6, 3, 1, 0),
                                                      Grade(7, 4, 1, 10),
                                                      Grade(8, 4, 1, 10),
                                                      Grade(9, 4, 2, 1)])
        self.grades_service.add_grade(3, 5, 2)
        self.assertEqual(self.grades_service.list(), [Grade(2, 3, 5, 1),
                                                      Grade(4, 2, 1, 10),
                                                      Grade(5, 2, 1, 0),
                                                      Grade(6, 3, 1, 0),
                                                      Grade(7, 4, 1, 10),
                                                      Grade(8, 4, 1, 10),
                                                      Grade(9, 4, 2, 1),
                                                      Grade(1, 3, 5, 2)])

class StatisticsServiceTests(unittest.TestCase):
    def setUp(self):
        grade_repository = GeneralRepository()
        student_repository = GeneralRepository()
        discipline_repository = GeneralRepository()
        undo_repository = UndoRepository()

        self.students_service = StudentsService(student_repository, undo_repository)
        self.disciplines_service = DisciplinesService(discipline_repository, undo_repository)
        self.grades_service = GradesService(grade_repository, student_repository, discipline_repository, undo_repository)
        self.statistics_service = StatisticsService(student_repository, discipline_repository, grade_repository)

        self.students_service.add_student(1, "Cineva")
        self.students_service.add_student(2, "Tu")
        self.students_service.add_student(3, "Altcineva")
        self.students_service.add_student(4, "idk")

        self.disciplines_service.add_discipline(1, "FP")
        self.disciplines_service.add_discipline(2, "CSA")
        self.disciplines_service.add_discipline(5, "Scoala vietii")

        self.grades_service.add_grade(1, 5, 10)
        self.grades_service.add_grade(3, 5, 1)
        self.grades_service.add_grade(1, 2, 4)
        self.grades_service.add_grade(2, 1, 10)
        self.grades_service.add_grade(2, 1, 0)
        self.grades_service.add_grade(3, 1, 0)
        self.grades_service.add_grade(4, 1, 10)
        self.grades_service.add_grade(4, 1, 10)
        self.grades_service.add_grade(4, 2, 1)

    def test_get_failing_students(self):
        self.assertEqual(self.statistics_service.get_failing_students(), [Student(1, "Cineva"),
                                                                          Student(3, "Altcineva"),
                                                                          Student(4, "idk")])

    def test_get_best_students(self):
        self.assertEqual(self.statistics_service.get_best_students(), [(Student(1, "Cineva"), 7),
                                                                       (Student(4, "idk"), 5.5),
                                                                       (Student(2, "Tu"), 5),
                                                                       (Student(3, "Altcineva"), 0.5)])

    def test_get_graded_disciplines(self):
        self.assertEqual(self.statistics_service.get_all_graded_disciplines(), [(Discipline(1, "FP"), 6),
                                                                                (Discipline(5, "Scoala vietii"), 5.5),
                                                                                (Discipline(2, "CSA"), 2.5)])


class UndoServiceTests(unittest.TestCase):
    def setUp(self):
        grade_repository = GeneralRepository()
        student_repository = GeneralRepository()
        discipline_repository = GeneralRepository()
        undo_repository = UndoRepository()
        self.students_service = StudentsService(student_repository, undo_repository)
        self.disciplines_service = DisciplinesService(discipline_repository, undo_repository)
        self.grades_service = GradesService(grade_repository, student_repository, discipline_repository, undo_repository)
        self.undo_service = UndoService(undo_repository)

        self.disciplines_service.add_discipline(3, "FP")
        self.students_service.add_student(1, "Cineva")
        self.grades_service.add_grade(1, 3, 2)
        self.students_service.add_student(2, "Altcineva")
        self.disciplines_service.update_discipline(3, "AAA")
        self.students_service.update_student(2, "Altcinevaaaa")
        self.grades_service.add_grade(2, 3, 1)
        self.grades_service.delete_student(1)
        self.grades_service.delete_discipline(3)

        self.students = [Student(2, "Altcinevaaaa")]

        self.disciplines = []

        self.grades = []

    def test_undo(self):
        def check_if_valid():
            self.assertEqual(self.students_service.list(), self.students)
            self.assertEqual(self.disciplines_service.list(), self.disciplines)
            self.assertEqual(self.grades_service.list(), self.grades)

        self.undo_service.undo()
        self.disciplines.append(Discipline(3, "AAA"))
        self.grades.append(Grade(2, 2, 3, 1))
        check_if_valid()

        self.undo_service.undo()
        self.grades.append(Grade(1, 1, 3, 2))
        self.students.append(Student(1, "Cineva"))
        check_if_valid()

        self.undo_service.undo()
        self.grades = [Grade(1, 1, 3, 2)]
        check_if_valid()

        self.undo_service.undo()
        self.students = [Student(2, "Altcineva"), Student(1, "Cineva")]
        check_if_valid()

        self.undo_service.undo()
        self.disciplines = [Discipline(3, "FP")]
        check_if_valid()

        self.undo_service.undo()
        self.students = [Student(1, "Cineva")]
        check_if_valid()

        self.undo_service.undo()
        self.grades = []
        check_if_valid()

        self.undo_service.undo()
        self.students = []
        check_if_valid()

    def test_redo(self):
        def check_if_valid():
            self.assertEqual(self.students_service.list(), self.students)
            self.assertEqual(self.disciplines_service.list(), self.disciplines)
            self.assertEqual(self.grades_service.list(), self.grades)

        self.undo_service.undo()
        self.disciplines.append(Discipline(3, "AAA"))
        self.grades.append(Grade(2, 2, 3, 1))
        check_if_valid()

        self.undo_service.undo()
        self.grades.append(Grade(1, 1, 3, 2))
        self.students.append(Student(1, "Cineva"))
        check_if_valid()

        self.undo_service.redo()
        self.grades.pop()
        self.students.pop()
        check_if_valid()

        self.students_service.add_student(10, "hmm")
        self.students.append(Student(10, "hmm"))
        self.undo_service.undo()
        self.undo_service.redo()
        check_if_valid()

    def test_clear(self):
        self.undo_service.clear()
        with self.assertRaises(UndoRepositoryException):
            self.undo_service.undo()