import unittest

from Domain.Taxi import Taxi
from Repository.GeneralRepository import GeneralRepository
from Services.RideService import RideService
from Services.TaxiService import TaxiService


class RideServiceTest(unittest.TestCase):
    def test_add_a_ride(self):
        taxi_repository = GeneralRepository()
        taxi = Taxi(0, 0, 0, 0)
        taxi2 = Taxi(1, 10, 0, 0)
        taxi_repository.add(taxi)
        taxi_repository.add(taxi2)
        taxi_service = TaxiService(taxi_repository)
        ride_service = RideService(taxi_repository)
        ride_service.process_ride_ui(4, 0, 10, 10)
        taxis = taxi_service.get_taxis_sorted_in_non_increasing_order_by_fare()
        self.assertEqual(len(taxis), 2)
        self.assertEqual(taxis[0], Taxi(0, 10, 10, 16))
        self.assertEqual(taxis[1], Taxi(1, 10, 0, 0))
