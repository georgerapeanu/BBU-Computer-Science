import random

from Domain.DistanceCalculator import DistanceCalculator
from Domain.Ride import Ride
from Domain.SimulatedRideDTO import SimulatedRideDTO
from Repository.GeneralRepository import GeneralRepository


class RideService:
    def __init__(self, taxi_repository):
        """ Constructor for RideService

        :param taxi_repository: taxi repository
        :type taxi_repository: GeneralRepository
        """

        self.__taxi_repository = taxi_repository

    def __find_closest_taxi_to_point(self, point):
        """ Find the closest taxi to a given point

        :param point: tuple containing coordinates of point
        :type point: tuple
        :return: taxi
        """

        best_taxi = None

        for repo_taxi in self.__taxi_repository.list():
            if best_taxi is None or DistanceCalculator.distance((best_taxi.x, best_taxi.y), point) > \
                                    DistanceCalculator.distance((repo_taxi.x, repo_taxi.y), point):
                best_taxi = repo_taxi
        return best_taxi

    def __process_ride(self, ride):
        """ This method processes a given ride

        :param ride: ride
        :type ride: Ride
        :return:
        """
        taxi = self.__find_closest_taxi_to_point(ride.start)
        taxi.fare += DistanceCalculator.distance(ride.start, ride.end)
        taxi.x = ride.end[0]
        taxi.y = ride.end[1]
        self.__taxi_repository.update(taxi.id, taxi)

    def process_ride_ui(self, start_x, start_y, end_x, end_y):
        """ This method processes a ride given its start and end coordinates
            This method is called by the UI

        :param start_x: x coordinate of ride
        :type start_x: int
        :param start_y: y coordinate of ride
        :type start_y: int
        :param end_x: x coordinate of ride
        :type end_x: int
        :param end_y: y coordinate of ride
        :type end_y: int
        :return:
        """

        start = (start_x, start_y)
        end = (end_x, end_y)
        ride = Ride(start, end)
        self.__process_ride(ride)

    def simulate_random_ride(self):
        """ This method simulates a random ride

        :return: SimulatedRideDTO
        """

        start = (random.randint(0, 100), random.randint(0, 100))
        end = (random.randint(0, 100), random.randint(0, 100))
        while DistanceCalculator.distance(start, end) < 10:
            end = (random.randint(0, 100), random.randint(0, 100))
        ride = Ride(start, end)
        taxi = self.__find_closest_taxi_to_point(start)
        self.__process_ride(ride)

        return SimulatedRideDTO(taxi, ride)
