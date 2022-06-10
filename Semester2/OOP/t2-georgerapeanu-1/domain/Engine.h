//
// Created by georgerapeanu on 05.05.2022.
//

#ifndef T2_GEORGERAPEANU_1_ENGINE_H
#define T2_GEORGERAPEANU_1_ENGINE_H

#include <string>

class Engine {
protected:
    std::string fuelType;
    double basePrice;
public:
    Engine(std::string fuelType, double basePrice);
    virtual double getPrice() = 0;
    virtual std::string toString() = 0;
};


#endif //T2_GEORGERAPEANU_1_ENGINE_H
