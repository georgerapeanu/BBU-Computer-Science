//
// Created by georgerapeanu on 05.05.2022.
//

#include "Service.h"
#include <fstream>
#include <cstdlib>

Engine *Service::createEngine(std::string engineType, std::string fuelType, int autonomy) {
    Engine* p_engine = NULL;

    if(engineType == "electric"){
        p_engine = new ElectricEngine(fuelType, 3000, autonomy);
    }else if(engineType == "turbo"){
        if(fuelType != "gasoline" && fuelType != "diesel"){
            throw AppException();
        }
        p_engine = new TurboEngine(fuelType, 3000);
    }else{
        throw AppException();
    }
    return p_engine;
}

Service::Service() {
    this->cars = std::vector<Car>();
}

Car Service::addCar(int numberOfDoors, std::string engineType, std::string fuelType, int autonomy) {
    if(numberOfDoors != 2 && numberOfDoors != 4){
        throw AppException();
    }
    Engine* p_engine = this->createEngine(engineType, fuelType, autonomy);
    Car tmp_car = Car(numberOfDoors, p_engine);
    this->cars.push_back(tmp_car);
    return tmp_car;
}

std::vector<Car> Service::getAllCars() {
    return this->cars;
}

std::vector<Car> Service::getCarsWithMaxPrice(double maxPrice) {
    std::vector<Car> ans;

    for(auto &car:this->cars){
        if(car.computePrice() < maxPrice){
            ans.push_back(car);
        }
    }

    return ans;
}

void Service::writeToFile(std::string fileName, std::vector<Car> &cars) {
    std::ofstream g(fileName);
    for(auto& car:cars){
        g << car.toString();
    }
    g.close();
}
