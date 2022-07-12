import unittest

from Repository.GeneralRepository import GeneralRepository
from Repository.RepositoryExceptions import GeneralRepositoryException


class TestEntity:
    def __init__(self, id, name):
        self.id = id
        self.name = name

    def __eq__(self, other):
        return self.id == other.id and self.name == other.name



class GeneralRepositoryTests(unittest.TestCase):
    def test_add(self):
        repository = GeneralRepository()
        repository.add(TestEntity(1, "ok"))
        self.assertEqual(repository.list(), [TestEntity(1, "ok")])
        repository.add(TestEntity(3, "ok2"))
        self.assertEqual(repository.list(), [TestEntity(1, "ok"), TestEntity(3, "ok2")])

    def test_update(self):
        repository = GeneralRepository()
        repository.add(TestEntity(1, "ok"))
        repository.add(TestEntity(3, "ok2"))
        repository.update(1, TestEntity(1, "aaaaa"))
        self.assertEqual(repository.list(), [TestEntity(1, "aaaaa"), TestEntity(3, "ok2")])

    def test_delete(self):
        repository = GeneralRepository()
        repository.add(TestEntity(1, "ok"))
        repository.add(TestEntity(3, "ok2"))
        repository.add(TestEntity(2, "aaaaaaaa"))
        repository.delete(3)
        self.assertEqual(repository.list(), [TestEntity(1, "ok"), TestEntity(2, "aaaaaaaa")])

    def test_list(self):
        repository = GeneralRepository()
        repository.add(TestEntity(1, "ok"))
        repository.add(TestEntity(3, "ok2"))
        repository.add(TestEntity(2, "aaaaaaaa"))
        self.assertEqual(repository.list(), [TestEntity(1, "ok"), TestEntity(3, "ok2"), TestEntity(2, "aaaaaaaa")])
        self.assertEqual(repository.get_by_id(1), TestEntity(1, "ok"))
        self.assertEqual(repository.get_by_id(4), None)

    def test_raises(self):
        repository = GeneralRepository()
        repository.add(TestEntity(1, "ok"))
        with self.assertRaises(GeneralRepositoryException):
            repository.add(TestEntity(1, "ok2"))

        with self.assertRaises(GeneralRepositoryException):
            repository.update(2, TestEntity(1, "ok2"))

        with self.assertRaises(GeneralRepositoryException):
            repository.update(2, TestEntity(2, "ok2"))

        with self.assertRaises(GeneralRepositoryException):
            repository.delete(2)

    def test_len(self):
        repository = GeneralRepository()
        self.assertEqual(len(repository), 0)
        repository.add(TestEntity(1, "ok"))
        self.assertEqual(len(repository), 1)
        repository.add(TestEntity(3, "ok2"))
        self.assertEqual(len(repository), 2)
