import unittest

from src.domain.Student import Student
from src.repository.Repository import RepositoryException
from src.services.StudentService import StudentService


class StudentServiceTests(unittest.TestCase):
    def test_constructor_populates_students(self):
        student_service = StudentService(23)
        self.assertEqual(len(student_service.get_students()), 23)

    def test_add_student(self):
        student_service = StudentService()
        student_service.add_student(1, "Eu", 916)
        student_service.add_student(3, "Ok", 917)
        self.assertListEqual(student_service.get_students(), [Student(1, "Eu", 916), Student(3, "Ok", 917)])
        self.assertRaises(RepositoryException, student_service.add_student, 1, "Impostor", 23)

    def test_filter_students(self):
        student_service = StudentService()
        student_service.add_student(1, "Eu", 916)
        student_service.add_student(3, "Ok", 917)
        student_service.filter(917)
        self.assertListEqual(student_service.get_students(), [Student(1, "Eu", 916)])

    def test_undo(self):
        student_service = StudentService()
        student_service.add_student(1, "Eu", 916)
        student_service.add_student(3, "Ok", 917)
        student_service.filter(917)
        self.assertListEqual(student_service.get_students(), [Student(1, "Eu", 916)])
        student_service.undo()
        self.assertListEqual(student_service.get_students(), [Student(1, "Eu", 916), Student(3, "Ok", 917)])
        student_service.undo()
        self.assertListEqual(student_service.get_students(), [Student(1, "Eu", 916)])
        student_service.undo()
        self.assertListEqual(student_service.get_students(), [])
        student_service = StudentService(10)
        self.assertRaises(RepositoryException, student_service.undo)


if __name__ == '__main__':
    unittest.main()
