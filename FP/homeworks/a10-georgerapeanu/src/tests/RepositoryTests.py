import unittest

from src.domain.ActionLeaf import ActionLeaf
from src.domain.Discipline import Discipline
from src.domain.UndoAction import UndoAction
from src.repository.BinaryRepository import BinaryRepository
from src.repository.RepositoryExceptions import GeneralRepositoryException, UndoRepositoryException, \
    TextFileRepositoryException
from src.repository.GeneralRepository import GeneralRepository
from src.domain.Student import Student
from src.repository.TextFileRepository import TextFileRepository
from src.repository.UndoRepository import UndoRepository
import os


class GeneralRepositoryTests(unittest.TestCase):
    def test_add(self):
        repository = GeneralRepository(Student)
        repository.add(Student(1, "ok"))
        self.assertEqual(repository.list(), [Student(1, "ok")])
        repository.add(Student(3, "ok2"))
        self.assertEqual(repository.list(), [Student(1, "ok"), Student(3, "ok2")])

    def test_update(self):
        repository = GeneralRepository(Student)
        repository.add(Student(1, "ok"))
        repository.add(Student(3, "ok2"))
        repository.update(1, Student(1, "aaaaa"))
        self.assertEqual(repository.list(), [Student(1, "aaaaa"), Student(3, "ok2")])

    def test_delete(self):
        repository = GeneralRepository(Student)
        repository.add(Student(1, "ok"))
        repository.add(Student(3, "ok2"))
        repository.add(Student(2, "aaaaaaaa"))
        repository.delete(3)
        self.assertEqual(repository.list(), [Student(1, "ok"), Student(2, "aaaaaaaa")])

    def test_list(self):
        repository = GeneralRepository(Student)
        repository.add(Student(1, "ok"))
        repository.add(Student(3, "ok2"))
        repository.add(Student(2, "aaaaaaaa"))
        self.assertEqual(repository.list(), [Student(1, "ok"), Student(3, "ok2"), Student(2, "aaaaaaaa")])
        self.assertEqual(repository.get_by_id(1), Student(1, "ok"))
        self.assertEqual(repository.get_by_id(4), None)

    def test_raises(self):
        repository = GeneralRepository(Student)
        repository.add(Student(1, "ok"))
        with self.assertRaises(GeneralRepositoryException):
            repository.add(Student(1, "ok2"))

        with self.assertRaises(GeneralRepositoryException):
            repository.update(2, Student(1, "ok2"))

        with self.assertRaises(GeneralRepositoryException):
            repository.update(2, Student(2, "ok2"))

        with self.assertRaises(GeneralRepositoryException):
            repository.delete(2)

    def test_len(self):
        repository = GeneralRepository(Student)
        self.assertEqual(len(repository), 0)
        repository.add(Student(1, "ok"))
        self.assertEqual(len(repository), 1)
        repository.add(Student(3, "ok2"))
        self.assertEqual(len(repository), 2)


class TextFileRepositoryTests(unittest.TestCase):
    def setUp(self):
        f = open("textfile_test","w") #just to check the following if
        if os.path.exists("textfile_test"):
            f.close()
            os.remove("textfile_test")
        self.__repository = TextFileRepository(Student, "textfile_test")

    def tearDown(self):
        if os.path.exists("textfile_test"):
            os.remove("textfile_test")

    def test_add(self):
        self.__repository.add(Student(1, "ok"))
        self.assertEqual(self.__repository.list(), [Student(1, "ok")])
        self.__repository.add(Student(3, "ok2"))
        self.assertEqual(self.__repository.list(), [Student(1, "ok"), Student(3, "ok2")])

    def test_update(self):
        self.__repository.add(Student(1, "ok"))
        self.__repository.add(Student(3, "ok2"))
        self.__repository.update(1, Student(1, "aaaaa"))
        self.assertEqual(self.__repository.list(), [Student(1, "aaaaa"), Student(3, "ok2")])

    def test_delete(self):
        self.__repository.add(Student(1, "ok"))
        self.__repository.add(Student(3, "ok2"))
        self.__repository.add(Student(2, "aaaaaaaa"))
        self.__repository.delete(3)
        self.assertEqual(self.__repository.list(), [Student(1, "ok"), Student(2, "aaaaaaaa")])

    def test_list(self):
        self.__repository.add(Student(1, "ok"))
        self.__repository.add(Student(3, "ok2"))
        self.__repository.add(Student(2, "aaaaaaaa"))
        self.assertEqual(self.__repository.list(), [Student(1, "ok"), Student(3, "ok2"), Student(2, "aaaaaaaa")])
        self.assertEqual(self.__repository.get_by_id(1), Student(1, "ok"))
        self.assertEqual(self.__repository.get_by_id(4), None)

    def test_raises(self):
        self.__repository.add(Student(1, "ok"))
        with self.assertRaises(GeneralRepositoryException):
            self.__repository.add(Student(1, "ok2"))

        with self.assertRaises(GeneralRepositoryException):
            self.__repository.update(2, Student(1, "ok2"))

        with self.assertRaises(GeneralRepositoryException):
            self.__repository.update(2, Student(2, "ok2"))

        with self.assertRaises(GeneralRepositoryException):
            self.__repository.delete(2)

    def test_len(self):
        self.assertEqual(len(self.__repository), 0)
        self.__repository.add(Student(1, "ok"))
        self.assertEqual(len(self.__repository), 1)
        self.__repository.add(Student(3, "ok2"))
        self.assertEqual(len(self.__repository), 2)

    def test_corrupt_file(self):
        student = Student(1, "ok")
        with open("textfile_corrupt", "w") as f:
            f.write(Student.to_file_string(student) + "\n")
            f.write(Student.to_file_string(student) + "\n")
        with self.assertRaises(TextFileRepositoryException):
            self.__repository = TextFileRepository(Student, "textfile_corrupt")
            self.__repository.load()
        if os.path.exists("textfile_corrupt"):
            os.remove("textfile_corrupt")


class BinaryRepositoryTests(unittest.TestCase):
    def setUp(self):
        f = open("binary_test", "w")  # just to check the following if
        if os.path.exists("binary_test"):
            f.close()
            os.remove("binary_test")
        self.__repository = BinaryRepository(Student, "binary_test")

    def tearDown(self):
        if os.path.exists("binary_test"):
            os.remove("binary_test")

    def test_add(self):
        self.__repository.add(Student(1, "ok"))
        self.assertEqual(self.__repository.list(), [Student(1, "ok")])
        self.__repository.add(Student(3, "ok2"))
        self.assertEqual(self.__repository.list(), [Student(1, "ok"), Student(3, "ok2")])

    def test_update(self):
        self.__repository.add(Student(1, "ok"))
        self.__repository.add(Student(3, "ok2"))
        self.__repository.update(1, Student(1, "aaaaa"))
        self.assertEqual(self.__repository.list(), [Student(1, "aaaaa"), Student(3, "ok2")])

    def test_delete(self):
        self.__repository.add(Student(1, "ok"))
        self.__repository.add(Student(3, "ok2"))
        self.__repository.add(Student(2, "aaaaaaaa"))
        self.__repository.delete(3)
        self.assertEqual(self.__repository.list(), [Student(1, "ok"), Student(2, "aaaaaaaa")])

    def test_list(self):
        self.__repository.add(Student(1, "ok"))
        self.__repository.add(Student(3, "ok2"))
        self.__repository.add(Student(2, "aaaaaaaa"))
        self.assertEqual(self.__repository.list(), [Student(1, "ok"), Student(3, "ok2"), Student(2, "aaaaaaaa")])
        self.assertEqual(self.__repository.get_by_id(1), Student(1, "ok"))
        self.assertEqual(self.__repository.get_by_id(4), None)

    def test_raises(self):
        self.__repository.add(Student(1, "ok"))
        with self.assertRaises(GeneralRepositoryException):
            self.__repository.add(Student(1, "ok2"))

        with self.assertRaises(GeneralRepositoryException):
            self.__repository.update(2, Student(1, "ok2"))

        with self.assertRaises(GeneralRepositoryException):
            self.__repository.update(2, Student(2, "ok2"))

        with self.assertRaises(GeneralRepositoryException):
            self.__repository.delete(2)

    def test_len(self):
        self.assertEqual(len(self.__repository), 0)
        self.__repository.add(Student(1, "ok"))
        self.assertEqual(len(self.__repository), 1)
        self.__repository.add(Student(3, "ok2"))
        self.assertEqual(len(self.__repository), 2)


class UndoRepositoryTests(unittest.TestCase):
    def setUp(self):
        self.general_repository = GeneralRepository(Discipline)
        self.undo_repository = UndoRepository()

    def test_undo_redo(self):
        self.general_repository.add(Discipline(1, "aa"))
        undo_action = ActionLeaf(self.general_repository.delete, tuple([1]))
        redo_action = ActionLeaf(self.general_repository.add, tuple([Discipline(1, "aa")]))
        self.undo_repository.add(UndoAction(undo_action, redo_action))
        self.assertEqual(self.general_repository.list(), [Discipline(1, "aa")])
        self.undo_repository.undo()
        self.assertEqual(self.general_repository.list(), [])
        self.undo_repository.redo()
        self.assertEqual(self.general_repository.list(), [Discipline(1, "aa")])
        self.undo_repository.undo()

        self.general_repository.add(Discipline(3, "bb"))
        undo_action = ActionLeaf(self.general_repository.add, tuple([Discipline(3, "bb")]))
        redo_action = ActionLeaf(self.general_repository.delete, tuple([1]))
        self.undo_repository.add(UndoAction(undo_action, redo_action))
        with self.assertRaises(UndoRepositoryException):
            self.undo_repository.redo()

    def test_exceptions(self):
        with self.assertRaises(UndoRepositoryException):
            self.undo_repository.redo()
        with self.assertRaises(UndoRepositoryException):
            self.undo_repository.undo()
