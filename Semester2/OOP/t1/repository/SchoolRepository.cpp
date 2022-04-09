//
// Created by georgerapeanu on 07.04.2022.
//

#include "SchoolRepository.h"
#include "AppException.h"

using namespace std;

SchoolRepository::SchoolRepository() {
    this->schools = vector<School>();
}

void SchoolRepository::add_school(School school) {
    for(auto repo_school:this->schools){
        if(repo_school.get_name() == school.get_name() && repo_school.get_lat() == school.get_lat() && repo_school.get_lon() == school.get_lon()){
            throw AppException("school already exists");
        }
    }
    this->schools.push_back(school);
}


void SchoolRepository::remove_school(School school) {
    int idx = -1;
    for(int i = 0;i < (int)this->schools.size();i++){
        School repo_school = this->schools[i];
        if(repo_school.get_name() == school.get_name() && repo_school.get_lat() == school.get_lat() && repo_school.get_lon() == school.get_lon()){
            idx = i;
            break;
        }
    }
    if(idx != -1){
        for(int i = idx;i + 1 < (int)this->schools.size();i++){
            this->schools[i] = this->schools[i + 1];
        }
        schools.pop_back();
    }else{
        throw AppException("school doesn't exist");
    }
}

vector<School> SchoolRepository::get_all_schools() {
    return this->schools;
}


void SchoolRepository::mark_school_as_visited(School school) {
    int idx = -1;
    for(int i = 0;i < (int)this->schools.size();i++){
        School repo_school = this->schools[i];
        if(repo_school.get_name() == school.get_name() && repo_school.get_lat() == school.get_lat() && repo_school.get_lon() == school.get_lon()){
            idx = i;
            break;
        }
    }
    if(idx != -1){
        this->schools[idx].set_visited(true);
    }else{
        throw AppException("school doesn't exist");
    }
}
