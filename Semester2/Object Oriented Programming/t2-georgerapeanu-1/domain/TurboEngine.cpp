//
// Created by georgerapeanu on 05.05.2022.
//

#include "TurboEngine.h"
#include <sstream>

double TurboEngine::getPrice() {
    if(this->fuelType == "gasoline"){
        return this->basePrice + 0.01 * 100;
    }
    return this->basePrice + 0.01 * 150;
}

std::string TurboEngine::toString() {
    std::ostringstream tmp;
    tmp << "Engine type: turbo\n";
    tmp << "Fuel type: " << this->fuelType << "\n";
    tmp << "Base price: " << this->basePrice << "\n";
    return tmp.str();
}

TurboEngine::TurboEngine(std::string fuelType, double basePrice) : Engine(fuelType, basePrice) {
    ;
}
