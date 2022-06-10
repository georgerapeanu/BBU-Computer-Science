//
// Created by georgerapeanu on 05.05.2022.
//

#ifndef T2_GEORGERAPEANU_1_TURBOENGINE_H
#define T2_GEORGERAPEANU_1_TURBOENGINE_H

#include "Engine.h"

class TurboEngine: public Engine{
public:
    TurboEngine(std::string fuelType, double basePrice);
    double getPrice() override;
    std::string toString() override;
};


#endif //T2_GEORGERAPEANU_1_TURBOENGINE_H
