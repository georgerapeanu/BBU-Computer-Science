from src.Domain.Exceptions import FlightServiceException
from src.Domain.Flight import Flight
from src.Repository.GenericFileRepository import GenericFileRepository


class FlightServiceValidator:
    """ This class implements a validator with methods for all required service level validation

    """

    @staticmethod
    def validate_flight(flight, flight_repository):
        """ Validates that a flight has the required properties. More exactly:
            flight times are between 15 and 90 minutes
            no two flights can have a common arrival or departure(i.e. all times are different)
            the uniqueness of the identifiers is verified by the repository

            Raises FlightServiceException if flight is invalid

        :param flight: the flight that should be validated
        :type flight: Flight
        :param flight_repository: the repository containing all flights
        :type flight_repository: GenericFileRepository
        :return: None
        """

        if flight.arrival_time - flight.departure_time < 15 or flight.arrival_time - flight.departure_time > 90:
            raise FlightServiceException("Flight duration is invalid")

        taken_times = {}
        for repo_flight in flight_repository.get_all():
            taken_times[repo_flight.arrival_time] = 1
            taken_times[repo_flight.departure_time] = 1

        if flight.arrival_time in taken_times or flight.departure_time in taken_times:
            raise FlightServiceException("Flight happens at the same time as another flight departure/arrival")
