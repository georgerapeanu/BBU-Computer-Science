//
// Created by georgerapeanu on 07.04.2022.
//

#ifndef T1_UI_H
#define T1_UI_H

#include "SchoolController.h"
#include <vector>

class UI {
    SchoolController* p_controller;

    void display_school(School school);
    void display_schools(std::vector<School> schools);
public:

    UI(SchoolController* p_controller);
    void run_ui();
};


#endif //T1_UI_H
