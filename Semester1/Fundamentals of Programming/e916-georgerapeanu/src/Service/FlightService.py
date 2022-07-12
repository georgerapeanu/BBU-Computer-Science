from copy import deepcopy

from src.Domain.Flight import Flight
from src.Repository.GenericFileRepository import GenericFileRepository
from src.Service.FlightServiceValidator import FlightServiceValidator


class FlightService:
    """ Implements the model for the flight service

    """

    def __init__(self, flight_repository):
        """ Constructor for FlightService

        :param flight_repository: the file repository used to store the files
        :type flight_repository: GenericFileRepository
        """
        self.__flight_repository = flight_repository

    def add_flight(self, flight_string):
        """ This method adds a flight given as a string(according to the format used also in the input file)

        :param flight_string: the flight string
        :type flight_string: str
        :return: None
        """

        flight = Flight.init_from_string(flight_string)
        FlightServiceValidator.validate_flight(flight, self.__flight_repository)
        self.__flight_repository.add(flight)

    def delete_flight(self, id):
        """ This method deletes the flight with the specified id

        :param id: the identifier of the flight
        :type id: str
        :return: None
        """
        self.__flight_repository.delete(id)

    def get_airport_activity(self):
        """ Returns a list containing tuples (airport, activity)
            activity = number of departures + number of arrivals
            the list is sorted decreasingly after the activity

        :return: list
        """

        activity = {}

        for repo_flight in self.__flight_repository.get_all():
            if repo_flight.arrival_city not in activity:
                activity[repo_flight.arrival_city] = 0
            if repo_flight.departure_city not in activity:
                activity[repo_flight.departure_city] = 0
            activity[repo_flight.arrival_city] += 1
            activity[repo_flight.departure_city] += 1

        ans = []

        for elem in activity.keys():
            ans.append([elem, activity[elem]])

        ans.sort(key=lambda x: x[1], reverse=True)

        return ans

    def __get_flight_as_events(self):
        """ Gets flights in an event fashion, so +1 means a flight becomes airborne and -1 means an airborne flight ended

        :return:
        """
        events = []
        for flight in self.__flight_repository.get_all():
            events.append([flight.departure_time, 1])
            events.append([flight.arrival_time, -1])
        events.sort(key=lambda x:x[0])
        return events

    def get_no_airborne_flight(self):
        """ Gets the intervals when there are no airborne flights, in decreasing order of length

        :return: list containing lists of length 2 [start, end]
        """
        ans = []
        active = 0
        last_time = 0

        events = self.__get_flight_as_events()

        for event in events:
            active += event[1]
            if active - event[1] == 0 and active != 0:
                ans.append([last_time, event[0]])
            elif active == 0:
                last_time = event[0]
        ans.sort(key=lambda x: x[1] - x[0],reverse=True)
        return ans

    def get_most_airborne_flights(self):
        """ Gets the intervals where there are the most airborne flights

        :return: list containing lists of length 2 [start, end]
        """

        ans = []
        most_flights = 0
        active = 0
        last_time = 0

        events = self.__get_flight_as_events()

        for event in events:
            active += event[1]
            if active > most_flights:
                most_flights = active
                last_time = event[0]
                ans = []
            elif active == most_flights:
                last_time = event[0]
            elif active < most_flights and active - event[1] >= most_flights:
                ans.append([last_time, event[0]])

        return ans

    def __get_flights_sorted_by_arrival_time(self):
        flights = deepcopy(self.__flight_repository.get_all())
        flights.sort(key=lambda x:x.arrival_time)
        return flights

    def get_at_most_one_airborne(self):
        """ Returns a list containing the flights which can be had in scenario 7

        :return: list of intervals [start,end]
        """

        ans = []

        for flight in self.__get_flights_sorted_by_arrival_time():
            if len(ans) == 0 or ans[-1].arrival_time <= flight.departure_time:
                ans.append(flight)
        return ans

