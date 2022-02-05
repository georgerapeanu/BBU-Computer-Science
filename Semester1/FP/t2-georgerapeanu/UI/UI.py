import re

from Services.RideService import RideService
from Services.TaxiService import TaxiService


class UI:
    def __init__(self, taxi_service, ride_service):
        """ Constructor for UI class

        :param taxi_service: taxi service
        :type taxi_service: TaxiService
        :param ride_service: ride service
        :type ride_service: RideService
        """
        self.__taxi_service = taxi_service
        self.__ride_service = ride_service

    def __display_help(self):
        print("Usage:")
        print("add ride from (x, y) to (x2, y2): adds a ride with specified endpoints")
        print("simulate n rides: simulates n random rides")
        print("help: displays help")
        print("exit: exits the program")

    def __print_error(self, s):
        print("Error: %s" % s)

    def __display_taxi(self, taxi):
        first_part = ("Taxi #%d" % taxi.id).ljust(8)
        second_part = ("current location: (%d, %d) and fare %d" % (taxi.x, taxi.y, taxi.fare)).rjust(20)
        print(first_part + " " + second_part)

    def __display_taxis(self):
        for taxi in self.__taxi_service.get_taxis_sorted_in_non_increasing_order_by_fare():
            self.__display_taxi(taxi)

    def __display_ride_dto(self, dto):
        print("Ride taken by taxi with id %d from (%d, %d) to (%d, %d)" % (dto.taxi.id, dto.ride.start[0], dto.ride.start[1], dto.ride.end[0], dto.ride.end[1]))

    def start(self):
        while True:
            try:
                n = int(input("Please enter the number of taxis:"))
                self.__taxi_service.add_multiple_random_taxis(n)
                break
            except Exception as ex:
                self.__print_error(str(ex))
        self.__display_taxis()
        self.__run_rides_only()

    def __run_rides_only(self):
        commands = [
            "^ *add +ride +from +[(] *[0-9]+ *, *[0-9]+ *[)] +to +[(] *[0-9]+ *, *[0-9]+ *[)] *$",
            "^ *simulate +[0-9]+ +rides *$",
            "^ *help *$",
            "^ *exit *$"
        ]

        while True:
            command = input("Please enter your command: ").strip()
            args = command.split(" ")
            if re.match(commands[0], command) is not None:
                halves = command.split("to")
                fst_point = halves[0].strip().split("from")[1]
                snd_point = halves[1].strip()
                start_x = int(fst_point.strip("( )").split(",")[0])
                start_y = int(fst_point.strip("( )").split(",")[1])
                end_x = int(snd_point.strip("( )").split(",")[0])
                end_y = int(snd_point.strip("( )").split(",")[1])
                self.__ride_service.process_ride_ui(start_x, start_y, end_x, end_y)
            elif re.match(commands[1], command) is not None:
                n = int(args[1])
                for i in range(n):
                    dto = self.__ride_service.simulate_random_ride()
                    self.__display_ride_dto(dto)
                    self.__display_taxis()
            elif re.match(commands[2], command) is not None:
                self.__display_help()
            elif re.match(commands[3], command) is not None:
                exit(0)
            else:
                print("Invalid_command")
                self.__display_help()
            self.__display_taxis()
