from Domain.Ride import Ride
from Domain.Taxi import Taxi


class SimulatedRideDTO:
    def __init__(self, taxi, ride):
        """ Constructor for this DTO

        :param taxi: taxi
        :type taxi: Taxi
        :param ride: ride
        :type ride: Ride
        """
        self.taxi = taxi
        self.ride = ride

    @property
    def taxi(self):
        return self.__taxi

    @taxi.setter
    def taxi(self, value):
        self.__taxi = value

    @property
    def ride(self):
        return self.__ride

    @ride.setter
    def ride(self, value):
        self.__ride = value
