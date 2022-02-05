import unittest

from src.Domain.Exceptions import FlightException, IdObjectException
from src.Domain.Flight import Flight
from src.Domain.IdObject import IdObject


class IdObjectTests(unittest.TestCase):
    def test_ok_scenario(self):
        tmp = IdObject(1)
        tmp = IdObject("aaa")

    def test_invalid_scenario(self):
        with self.assertRaises(IdObjectException):
            tmp = IdObject([])


class FlightObjectTests(unittest.TestCase):
    def test_init(self):
        tmp = Flight("assa", "Cluj", 0, "Iasi", 20)
        with self.assertRaises(FlightException):
            tmp = Flight(1, "Cluj", 0, "Iasi", 20)
        with self.assertRaises(FlightException):
            tmp = Flight("aaaa", 2, 0, "Iasi", 20)
        with self.assertRaises(FlightException):
            tmp = Flight("1", "Cluj", "a", "Iasi", 20)
        with self.assertRaises(FlightException):
            tmp = Flight("1", "Cluj", 0, 1, 20)
        with self.assertRaises(FlightException):
            tmp = Flight("1", "Cluj", 0, "Iasi", "20")
        with self.assertRaises(FlightException):
            tmp = Flight("1", "Cluj", -1, "Iasi", 20)
        with self.assertRaises(FlightException):
            tmp = Flight("1", "Cluj", 0, "Iasi", 22000000)
        tmp = Flight("1", "Cluj", 20, "Iasi", 0) #logic should be handled by domain and therefore it shall not raise anything


    def test_getters(self): #setters are implicitly tested by init
        tmp = Flight("assa", "Cluj", 0, "Iasi", 20)
        self.assertEqual(tmp.id, "assa")
        self.assertEqual(tmp.departure_city, "Cluj")
        self.assertEqual(tmp.departure_time, 0)
        self.assertEqual(tmp.arrival_city, "Iasi")
        self.assertEqual(tmp.arrival_time, 20)

    def test_str(self):
        tmp = Flight("assa", "Cluj", 0, "Iasi", 20)
        self.assertEqual(str(tmp), "assa,Cluj,00:00,Iasi,00:20")

    def test_init_from_str(self):
        tmp = Flight.init_from_string("assa,Cluj,00:00,Iasi,00:20")
        self.assertEqual(tmp, Flight("assa", "Cluj", 0, "Iasi", 20))
        with self.assertRaises(Exception):
            Flight.init_from_string("assa,Cluj,00:00,00:20")
        with self.assertRaises(FlightException):
            Flight.init_from_string(2)

    def test_eq(self):
        tmp = Flight("assa", "Cluj", 0, "Iasi", 20)
        tmp2 = Flight("assa", "Cluj", 0, "Iasi", 20)
        self.assertEqual(tmp, tmp2)
        tmp2.arrival_city = "Bucuresti"
        self.assertNotEqual(tmp, tmp2)
