//
// Created by georgerapeanu on 05.05.2022.
//

#ifndef T2_GEORGERAPEANU_1_CAR_H
#define T2_GEORGERAPEANU_1_CAR_H

#include "Engine.h"

class Car {
private:
    int numberOfDoors;
    Engine* p_engine;
public:
    Car(int numberOfDoors, Engine* p_engine);
    double computePrice();
    std::string toString();
};


#endif //T2_GEORGERAPEANU_1_CAR_H
