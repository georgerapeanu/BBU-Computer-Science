//
// Created by georgerapeanu on 07.04.2022.
//

#include "UI.h"
#include "AppException.h"
#include <iostream>
#include <iomanip>

using namespace std;

void UI::run_ui() {
    while(true){
        cout << "Please select an option:" << endl;
        cout << "1. Add a school" << endl;
        cout << "2. Remove a school" << endl;
        cout << "3. Get all schools sorted by name" << endl;
        cout << "4. Mark all schools before a given date as visited and print all unvisited schools after that date" << endl;
        cout << "5. Exit" << endl;
        try{
            int option;
            cin >> option;

            if(option == 1){
                string name;
                double lat, lon;
                string date;
                string visited;
                bool actual_visited;

                cout << "Please enter the school's name: " << endl;
                cin >> name;
                cout << "Please enter the school's latitude: " << endl;
                cin >> lat;
                cout << "Please enter the school's longitude: " << endl;
                cin >> lon;
                cout << "Please enter the school's date: " << endl;
                cin >> date;
                cout << "Please enter the school's visited status: " << endl;
                cin >> visited;
                actual_visited = (visited == "true");
                p_controller->add_school(name, lat, lon, date, actual_visited);
            }else if(option == 2){
                string name;
                double lat, lon;
                cout << "Please enter the school's name: " << endl;
                cin >> name;
                cout << "Please enter the school's latitude: " << endl;
                cin >> lat;
                cout << "Please enter the school's longitude: " << endl;
                cin >> lon;
                p_controller->remove_school(name, lat, lon);
            }else if(option == 3){
                display_schools(p_controller->get_all_schools_sorted_by_name());
            }else if(option == 4){
                cout << "Please enter the date: " << endl;
                string date;
                cin >> date;
                p_controller->mark_all_schools_as_visited_before_date(date);
                display_schools(this->p_controller->get_all_schools_unvisited_after_date(date));
            }else if(option == 5){
                break;
            }else{
                throw AppException("Invalid command!");
            }
            cout << "Operation successful!" << endl;
        }catch(AppException &ex){
            cout << "Error: " << ex.get_message() << endl;
        }
    }
}

UI::UI(SchoolController* p_controller) {
    this->p_controller = p_controller;
}

void UI::display_school(School school) {
    cout << school.get_name() << " | ";
    cout << fixed << setprecision(2) << school.get_lat() << ", " << school.get_lon() << " | ";
    cout << school.get_date() << " | ";
    cout << (school.get_visited() ? "true":"false") << endl;
}

void UI::display_schools(std::vector<School> schools) {
    for(auto school:schools){
        display_school(school);
    }
}
