import unittest

from src.domain.Student import Student
from src.repository.Repository import Repository, RepositoryException


class RepositoryTests(unittest.TestCase):
    def test_constructor_populates_students(self):
        repository = Repository(23)
        self.assertEqual(len(repository.get_students()), 23)

    def test_add_student(self):
        repository = Repository()
        repository.add_student(Student(1, "Eu", 916))
        repository.add_student(Student(3, "Ok", 917))
        self.assertListEqual(repository.get_students(), [Student(1, "Eu", 916), Student(3, "Ok", 917)])
        self.assertRaises(RepositoryException, repository.add_student, Student(1, "Impostor", 23))

    def test_filter_students(self):
        repository = Repository()
        repository.add_student(Student(1, "Eu", 916))
        repository.add_student(Student(3, "Ok", 917))
        repository.filter(lambda x: x.group == 916)
        self.assertListEqual(repository.get_students(), [Student(1, "Eu", 916)])

    def test_undo(self):
        repository = Repository()
        repository.add_student(Student(1, "Eu", 916))
        repository.add_student(Student(3, "Ok", 917))
        repository.filter(lambda x: x.group == 916)
        self.assertListEqual(repository.get_students(), [Student(1, "Eu", 916)])
        repository.undo()
        self.assertListEqual(repository.get_students(), [Student(1, "Eu", 916), Student(3, "Ok", 917)])
        repository.undo()
        self.assertListEqual(repository.get_students(), [Student(1, "Eu", 916)])
        repository.undo()
        self.assertListEqual(repository.get_students(), [])
        repository = Repository(10)
        self.assertRaises(RepositoryException, repository.undo)


if __name__ == '__main__':
    unittest.main()
