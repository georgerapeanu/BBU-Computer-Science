import unittest

from src.utils import utils
from src.utils.CustomIterable import CustomIterable


class CustomIterableTests(unittest.TestCase):
    def setUp(self):
        self.__iterable = CustomIterable()
        self.__iterable[1] = 2
        self.__iterable[3] = -1

    def tearDown(self):
        del self.__iterable

    def test_get_item(self):
        self.assertEqual(self.__iterable[1], 2)
        self.assertEqual(self.__iterable[3], -1)
        with self.assertRaises(KeyError):
            tmp = self.__iterable[2]

    def test_set_item(self):
        self.__iterable[2] = 3
        self.assertEqual(self.__iterable[2], 3)

    def test_del_item(self):
        with self.assertRaises(KeyError):
            del self.__iterable[2]
        del self.__iterable[3]
        with self.assertRaises(KeyError):
            tmp = self.__iterable[3]

    def test_contains(self):
        self.assertEqual(1 in self.__iterable, True)
        self.assertEqual(2 in self.__iterable, False)
        self.assertEqual(3 in self.__iterable, True)

    def test_len(self):
        self.assertEqual(len(self.__iterable), 2)

    def test_iter(self):
        start = iter(self.__iterable)
        self.assertEqual(next(start), 2)
        self.assertEqual(next(start), -1)


class UtilsTests(unittest.TestCase):
    def setUp(self):
        self.__iterable = CustomIterable()
        self.__iterable[1] = 2
        self.__iterable[3] = -1
        self.__iterable[4] = 5

    def tearDown(self):
        del self.__iterable

    def test_filter(self):
        self.assertEqual(utils.Utils.filter(self.__iterable, lambda x: x > 0), [2, 5])

    def test_sort(self):
        self.assertEqual(utils.Utils.sort(self.__iterable, lambda a, b: a < b), [-1, 2, 5])
