import unittest

from src.domain.Student import Student
from src.domain.StudentValidator import StudentValidatorException


class StudentTests(unittest.TestCase):
    def test_constructor_validation(self):
        self.assertRaises(StudentValidatorException, Student, -1, "Test", 2)
        self.assertRaises(StudentValidatorException, Student, 1, "    ", 2)
        self.assertRaises(StudentValidatorException, Student, 1, "Ok", 0)
        Student(2, "OK", 2)

    def test_getters(self):
        student = Student(1, "Test", 2)
        self.assertEqual(student.id, 1)
        self.assertEqual(student.name, "Test")
        self.assertEqual(student.group, 2)

    def test_setters(self):
        student = Student(1,"Test",2)
        student.name = "tEST2"
        student.group = 3
        self.assertEqual(student.name, "tEST2")
        self.assertEqual(student.group, 3)


if __name__ == '__main__':
    unittest.main()
