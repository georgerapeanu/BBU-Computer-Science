//
// Created by georgerapeanu on 07.04.2022.
//

#include "SchoolController.h"

#include<string>
#include <vector>
#include <algorithm>

using namespace std;

void SchoolController::add_school(string name, double lat, double lon, string date, bool visited) {
    this->repository.add_school(School(name, lat, lon, date, visited));
}


void SchoolController::remove_school(string name, double lat, double lon) {
    this->repository.remove_school(School(name, lat, lon,"invalid",false));
}

vector<School> SchoolController::get_all_schools_sorted_by_name() {
    vector<School> ans = this->repository.get_all_schools();
    sort(ans.begin(), ans.end(), [&](School &a, School &b){
       return a.get_name() < b.get_name();
    });
    return ans;
}

void SchoolController::mark_all_schools_as_visited_before_date(string date) {
    vector<School> schools = this->repository.get_all_schools();
    for(auto school:schools){
        if(school.date_before(date)){
            if(school.get_visited() == false){
                this->repository.mark_school_as_visited(school);
            }
        }
    }
}

vector<School> SchoolController::get_all_schools_unvisited_after_date(string date) {
    vector<School> ans;
    vector<School> schools = this->repository.get_all_schools();
    for(auto school:schools){
        if(!school.date_before(date)){
            if(school.get_visited() == false){
                ans.push_back(school);
            }
        }
    }
    return ans;
}

SchoolController::SchoolController() {
    this->repository = SchoolRepository();
}
