from src.Domain.Flight import Flight
from src.Repository.GenericFileRepository import GenericFileRepository
from src.Service.FlightService import FlightService
from src.UI.UI import UI

if __name__ == "__main__":
    flight_repository = GenericFileRepository(Flight, "input.txt")
    flight_service = FlightService(flight_repository)
    ui = UI(flight_service)
    ui.run()
