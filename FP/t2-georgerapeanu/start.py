from Repository.GeneralRepository import GeneralRepository
from Services.RideService import RideService
from Services.TaxiService import TaxiService
from UI.UI import UI

if __name__ == "__main__":
    taxi_repository = GeneralRepository()
    taxi_service = TaxiService(taxi_repository)
    ride_service = RideService(taxi_repository)
    ui = UI(taxi_service, ride_service)
    ui.start()