//
// Created by georgerapeanu on 05.05.2022.
//

#include "UI.h"
#include <iostream>
#include "Car.h"

UI::UI() {
    this->service = Service();
}

void UI::handleShowCars() {
    for(auto &car:this->service.getAllCars()){
        std::cout << car.toString() << std::endl;
    }
}

void UI::handleAddCar() {
    int numberOfDoors = -1;
    std::string engineType = "";
    std::string fuelType = "";
    int autonomy = 0;
    if(get_valid_option("Select number of doors(enter 0 for 2 and 1 for 4):", 0, 1) == 0) {
        numberOfDoors = 2;
    }else{
        numberOfDoors = 4;
    }
    if(get_valid_option("Select the engine type(enter 0 for electric and 1 for turbo):", 0, 1) == 0) {
        engineType = "electric";
    }else{
        engineType = "turbo";
    }
    if(engineType == "turbo") {
        if (get_valid_option("Select the fuel type(enter 0 for gasoline and 1 for diesel):", 0, 1) == 0) {
            fuelType = "gasoline";
        } else {
            fuelType = "diesel";
        }
    }else{
        std::cout << "Please enter the autonomy: ";
        std::cin >> autonomy;
    }
    std::cout << this->service.addCar(numberOfDoors, engineType, fuelType, autonomy).toString();
}

int UI::get_valid_option(std::string prompt, int __min, int __max) {
    int option = -1;
    while(true){
        std::string raw_input;
        std::cout << prompt;
        std::cin >> raw_input;
        try {
            option = stoi(raw_input);
            if (__min <= option && option <= __max) {
                break;
            }
        } catch(std::exception &ex){
            ;
        }
        std::cout << "Invalid option" << std::endl;
    }
    return option;
}

void UI::handleSaveToFileAllCarsWithPriceLessThan() {
    double price;
    std::string filename;
    std::cout << "Enter the desired filename:";
    std::cin >> filename;
    std::cout << "Enter the desired price:";
    std::cin >> price;
    std::vector<Car> tmp = this->service.getCarsWithMaxPrice(price);
    this->service.writeToFile(filename, tmp);
}

void UI::runUi() {
    while(true){
        int option = get_valid_option("press 0 to exit, 1 to add a car, 2 to show all cars, 3 to save cars to file:", 0, 3);
        try{
            if(option == 0){
                break;
            }else if(option == 1){
                this->handleAddCar();
            }else if(option == 2){
                this->handleShowCars();
            }else{
                this->handleSaveToFileAllCarsWithPriceLessThan();
            }
        } catch (AppException &exception){
            std::cout << "Invalid input";
        }
    }
}

