//
// Created by georgerapeanu on 05.05.2022.
//

#ifndef T2_GEORGERAPEANU_1_ELECTRICENGINE_H
#define T2_GEORGERAPEANU_1_ELECTRICENGINE_H

#include "Engine.h"
#include <string>

class ElectricEngine: public Engine{
private:
    int autonomy;
public:
    ElectricEngine(std::string fuelType, double basePrice, int autonomy);
    double getPrice() override;
    std::string toString() override;
};


#endif //T2_GEORGERAPEANU_1_ELECTRICENGINE_H
