
from src.Service.FlightService import FlightService
import re


class UI:
    """ Model for UI class

    """
    def __init__(self, flight_service):
        """ Constructor for UI

        :param flight_service: the flight service UI uses
        :type flight_service: FlightService
        """
        self.__flight_service = flight_service

    def display_help(self):
        print("Commands:")
        print("add flight ID,DCITY,DHH:DMM,ACITY,AHH:AMM")
        print("\tadds a flight from the above data. The string should follow the format used in the persistent file")
        print("delete flight ID")
        print("\tdeletes flight with id")
        print("list airports by activity")
        print("\tlists the airports decreasingly by the activity")
        print("list intervals no airborne flights")
        print("\tlists the intervals during which there were no airborne flights")
        print("list intervals maximum number of airborne flights")
        print("\tlists the intervals during which the maximum number of airborne flights took place")
        print("list flights in case of failure")
        print("\t prints the maximum number of flights and the flights which could still be taken in case the backup radar is used")
        print("help")
        print("\t displays help prompt")
        print("exit")
        print("exits the program")

    def display_activity(self, activity_list):
        for elem in activity_list:
            print("Airport %s has %d flights daily" % (elem[0], elem[1]))

    def display_intervals(self, intervals):
        for interval in intervals:
            print("Interval [%.2d:%.2d - %.2d:%.2d]" % (interval[0] // 60, interval[0] % 60, interval[1] // 60, interval[1] % 60))

    def display_flight(self, flight):
        (departure_hour, departure_minute) = (flight.departure_time // 60, flight.departure_time % 60)
        (arrival_hour, arrival_minute) = (flight.arrival_time // 60, flight.arrival_time % 60)
        print("%.2d:%.2d | %.2d:%.2d | %s | %s - %s" % (departure_hour, departure_minute, arrival_hour, arrival_minute, flight.id, flight.departure_city, flight.arrival_city))

    def display_flights(self, flights):
        for flight in flights:
            self.display_flight(flight)

    def run(self):
        commands = [
            "^ *add +flight .+$",
            "^ *delete +flight .+$",
            "^ *list +airports +by +activity *$",
            "^ *list +intervals +no +airborne +flights *$",
            "^ *list +intervals +maximum +number +of +airborne +flights *$",
            "^ *list +flights +in +case +of +failure *$",
            "^ *help *$",
            "^ *exit *$"
        ]

        while True:
            command = input("Enter your command: ")
            try:
                if re.match(commands[0], command) is not None:
                    self.__flight_service.add_flight(command.split("flight", maxsplit=1)[1].strip())
                elif re.match(commands[1], command) is not None:
                    self.__flight_service.delete_flight(command.split("flight", maxsplit=1)[1].strip())
                elif re.match(commands[2], command) is not None:
                    self.display_activity(self.__flight_service.get_airport_activity())
                elif re.match(commands[3], command) is not None:
                    self.display_intervals(self.__flight_service.get_no_airborne_flight())
                elif re.match(commands[4], command) is not None:
                    self.display_intervals(self.__flight_service.get_most_airborne_flights())
                elif re.match(commands[5], command) is not None:
                    self.display_flights(self.__flight_service.get_at_most_one_airborne())
                elif re.match(commands[6], command) is not None:
                    self.display_help()
                elif re.match(commands[7], command) is not None:
                    exit(0)
                else:
                    print("Invalid command")
                    self.display_help()
            except Exception as ex:
                print("Error: " + str(ex))
