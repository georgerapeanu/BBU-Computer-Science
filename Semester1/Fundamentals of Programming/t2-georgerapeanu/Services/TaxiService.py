import random
from copy import deepcopy

from Domain.DistanceCalculator import DistanceCalculator
from Domain.Taxi import Taxi
from Repository.GeneralRepository import GeneralRepository


class TaxiService:
    def __init__(self, taxi_repository):
        """ Constructor for taxi service

        :param taxi_repository: taxi repository
        :type taxi_repository: GeneralRepository
        """
        self.__taxi_repository = taxi_repository

    def __can_add_taxi(self, taxi):
        """ Verifies if the given taxi can be added to the repository in order to satisfy
            the condition from requirement 1

        :param taxi: taxi
        :type taxi: Taxi
        :return: True if it can be added False otherwise
        """
        for repo_taxi in self.__taxi_repository.list():
            if DistanceCalculator.distance((taxi.x, taxi.y), (repo_taxi.x, repo_taxi.y)) <= 5:
                return False
        return True

    def __add_a_random_taxi(self):
        """ Adds a random taxi that satisfies the requirement from feature 1

        :return:
        """
        while True:
            taxi = Taxi(len(self.__taxi_repository), random.randint(0, 100), random.randint(0, 100), 0)

            if self.__can_add_taxi(taxi):
                self.__taxi_repository.add(taxi)
                break

    def add_multiple_random_taxis(self, n):
        """

        :param n: the number of taxi's to be added
        :type n: int
        :return:
        """

        for i in range(0, n):
            self.__add_a_random_taxi()

    def get_taxis_sorted_in_non_increasing_order_by_fare(self):
        """ Returns a list of taxis sorted non increasingly by their total fare

        :return:
        """
        taxis = deepcopy(self.__taxi_repository.list())
        taxis = sorted(taxis, key=lambda taxi: taxi.fare, reverse=True)
        return taxis
    