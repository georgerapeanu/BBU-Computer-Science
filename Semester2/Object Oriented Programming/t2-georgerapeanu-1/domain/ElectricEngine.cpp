//
// Created by georgerapeanu on 05.05.2022.
//

#include "ElectricEngine.h"
#include <sstream>

ElectricEngine::ElectricEngine(std::string fuelType, double basePrice, int autonomy) : Engine(fuelType, basePrice) {
    this->autonomy = autonomy;
}

double ElectricEngine::getPrice() {
    return this->basePrice + this->autonomy * 0.01;
}

std::string ElectricEngine::toString() {
    std::ostringstream tmp;
    tmp << "Engine type: electric\n";
    tmp << "Autonomy: " << this->autonomy << "\n";
    tmp << "Fuel type: " << this->fuelType << "\n";
    tmp << "Base price: " << this->basePrice << "\n";
    return tmp.str();
}
