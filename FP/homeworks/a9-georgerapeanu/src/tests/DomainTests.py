import unittest
from src.domain.DomainExceptions import StudentException, DisciplineException, GradeException
from src.domain.Student import Student
from src.domain.Discipline import Discipline
from src.domain.Grade import Grade


class StudentTests(unittest.TestCase):
    def test_student_getters(self):
        student = Student(1, "aaaa")
        self.assertEqual(student.id, 1)
        self.assertEqual(student.name, "aaaa")

    def test_student_setters(self):
        student = Student(1, "aaaa")
        student.name = "abas"
        self.assertEqual(student.id, 1)
        self.assertEqual(student.name, "abas")

    def test_student_exceptions(self):
        self.assertRaises(StudentException, Student, "", "aaaa")
        self.assertRaises(StudentException, Student, 1, 2)
        self.assertRaises(StudentException, Student, 1, "    ")
        student = Student(-3, "okok")
        with self.assertRaises(StudentException):
            student.name = "     "

    def test_str(self):
        student = Student(2, "aaa")
        self.assertEqual(str(student), "Student #2: aaa")
        self.assertEqual(Student.to_file_string(student), "2,aaa")
        self.assertEqual(Student.from_file_string("2,aaa"), student)
        with self.assertRaises(StudentException):
            Student.from_file_string("2")
        with self.assertRaises(StudentException):
            Student.from_file_string("2,")

    def test_eq(self):
        student1 = Student(1, "test1")
        student2 = Student(2, "test2")
        self.assertEqual(student1, student1)
        self.assertEqual(student2, student2)
        self.assertNotEqual(student1, student2)


class DisciplineTests(unittest.TestCase):
    def test_discipline_getters(self):
        discipline = Discipline(4, "ceva")
        self.assertEqual(discipline.id, 4)
        self.assertEqual(discipline.name, "ceva")

    def test_discipline_setters(self):
        discipline = Discipline(5, "ceva2")
        discipline.name = "okokkokokoko"
        self.assertEqual(discipline.id, 5)
        self.assertEqual(discipline.name, "okokkokokoko")

    def test_discipline_raises(self):
        self.assertRaises(DisciplineException, Discipline, "", "disciplina")
        self.assertRaises(DisciplineException, Discipline, 0, 1)
        self.assertRaises(DisciplineException, Discipline, 1, "")
        discipline = Discipline(-4, "ok")
        with self.assertRaises(DisciplineException):
            discipline.name = " "

    def test_str(self):
        discipline = Discipline(4, "ok")
        self.assertEqual(str(discipline), "Discipline #4: ok")
        self.assertEqual(Discipline.to_file_string(discipline), "4,ok")
        self.assertEqual(Discipline.from_file_string("4,ok"), discipline)
        with self.assertRaises(DisciplineException):
            Discipline.from_file_string("2")
        with self.assertRaises(DisciplineException):
            Discipline.from_file_string("2,")

    def test_eq(self):
        discipline1 = Discipline(1, "test1")
        discipline2 = Discipline(2, "test2")
        self.assertEqual(discipline1, discipline1)
        self.assertEqual(discipline2, discipline2)
        self.assertNotEqual(discipline1, discipline2)


class GradeTests(unittest.TestCase):
    def test_grade_getters(self):
        grade = Grade(7, 1, 3, 2)
        self.assertEqual(grade.id, 7)
        self.assertEqual(grade.student_id, 1)
        self.assertEqual(grade.discipline_id, 3)
        self.assertEqual(grade.grade, 2)

    def test_grade_setters(self):
        grade = Grade(7, 1, 3, 2)
        grade.grade = 10
        self.assertEqual(grade.id, 7)
        self.assertEqual(grade.student_id, 1)
        self.assertEqual(grade.discipline_id, 3)
        self.assertEqual(grade.grade, 10)

    def test_grade_raises(self):
        self.assertRaises(GradeException, Grade, "", 1, 2, 2)
        self.assertRaises(GradeException, Grade, 7, "", 2, 2)
        self.assertRaises(GradeException, Grade, 7, 1, 1.2, 2)
        self.assertRaises(GradeException, Grade, 7, 23, 3, -1)
        self.assertRaises(GradeException, Grade, 7, 23, 3, 11)
        self.assertRaises(GradeException, Grade, 7, 23, 3, "")
        grade = Grade(10, 20, 29, 0)
        with self.assertRaises(GradeException):
            grade.grade = 11

    def test_str(self):
        grade = Grade(10, 1, 2, 5)
        self.assertEqual(str(grade), "Grade #10 of student 1 at 2 : 5")
        self.assertEqual(Grade.to_file_string(grade), "10,1,2,5")
        self.assertEqual(Grade.from_file_string("10,1,2,5"), grade)
        with self.assertRaises(GradeException):
            Grade.from_file_string("")
        with self.assertRaises(GradeException):
            Grade.from_file_string("1,1,,1")

    def test_eq(self):
        grade1 = Grade(1, 2, 3, 4)
        grade2 = Grade(4, 3, 2, 1)
        self.assertEqual(grade1, grade1)
        self.assertEqual(grade2, grade2)
        self.assertNotEqual(grade1, grade2)
