import unittest

from Domain.Exceptions import FlightException, GenericFileRepositoryException, FlightServiceException
from Domain.Flight import Flight
from Repository.GenericFileRepository import GenericFileRepository
from Service.FlightService import FlightService
import os


class FlightServiceTests(unittest.TestCase):
    def setUp(self):
        if os.path.exists("test.txt"):
            os.remove("test.txt")
        self.__flight_repository = GenericFileRepository(Flight, "test.txt")
        self.__flight_service = FlightService(self.__flight_repository)

    def test_add_flight(self):
        self.__flight_service.add_flight("aaaa,Cluj,20:00,Bucuresti,20:50")
        with self.assertRaises(Exception):
            self.__flight_service.add_flight("aaaa2")
        with self.assertRaises(Exception):
            self.__flight_service.add_flight("aaaa2,Cluj,20:00,Bucuresti,22:00")
        with self.assertRaises(Exception):
            self.__flight_service.add_flight("aaaa2,Cluj,20:00,Bucuresti,20:01")
        with self.assertRaises(Exception):
            self.__flight_service.add_flight("aaaa,Cluj,21:00,Iasi,21:50")
        with self.assertRaises(Exception):
            self.__flight_service.add_flight("aaaa2,Cluj,20:00,Iasi,20:30")
        with self.assertRaises(Exception):
            self.__flight_service.add_flight("aaaa2,Cluj,20:10,Iasi,20:50")
