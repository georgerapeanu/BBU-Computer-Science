//
// Created by georgerapeanu on 05.05.2022.
//

#ifndef T2_GEORGERAPEANU_1_UI_H
#define T2_GEORGERAPEANU_1_UI_H

#include "Car.h"
#include "Service.h"

class UI {
    int get_valid_option(std::string prompt, int __min, int __max);
private:
    Service service;
    void handleAddCar();
    void handleShowCars();
    void handleSaveToFileAllCarsWithPriceLessThan();
public:
    UI();
    void runUi();
};


#endif //T2_GEORGERAPEANU_1_UI_H
