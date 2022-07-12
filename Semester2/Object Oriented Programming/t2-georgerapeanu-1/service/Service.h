//
// Created by georgerapeanu on 05.05.2022.
//

#ifndef T2_GEORGERAPEANU_1_SERVICE_H
#define T2_GEORGERAPEANU_1_SERVICE_H

#include "Car.h"
#include "AppException.h"
#include "Engine.h"
#include "ElectricEngine.h"
#include "TurboEngine.h"
#include <vector>

class Service {
    std::vector<Car> cars;

    Engine* createEngine(std::string engineType, std::string fuelType, int autonomy);
public:

    Service();
    Car addCar(int numberOfDoors, std::string engineType, std::string fuelType, int autonomy);
    std::vector<Car> getAllCars();
    std::vector<Car> getCarsWithMaxPrice(double maxPrice);
    void writeToFile(std::string fileName, std::vector<Car> &cars);

};


#endif //T2_GEORGERAPEANU_1_SERVICE_H
