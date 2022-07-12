//
// Created by georgerapeanu on 05.05.2022.
//

#include "Car.h"
#include <sstream>

double Car::computePrice() {
    return 7000 + (this->numberOfDoors == 4) * 1500 + this->p_engine->getPrice();
}

Car::Car(int numberOfDoors, Engine* p_engine) {
    this->numberOfDoors = numberOfDoors;
    this->p_engine = p_engine;
}

std::string Car::toString() {
    std::ostringstream tmp;
    tmp << "Car with " << this->numberOfDoors << " doors\n";
    tmp << this->p_engine->toString();
    tmp << "Price: " << this->computePrice() << std::endl;
    return tmp.str();
}
