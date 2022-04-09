//
// Created by georgerapeanu on 07.04.2022.
//

#include "School.h"
#include <vector>
#include <algorithm>
#include "utils.h"

using namespace std;

School::School(string name, double lat, double lon, string date, bool visited) {
    this->name = name;
    this->lat = lat;
    this->lon = lon;
    this->date = date;
    this->visited = visited;
}

double School::get_lat() {
    return lat;
}

string School::get_name() {
    return name;
}

double School::get_lon() {
    return lon;
}

string School::get_date() {
    return date;
}

bool School::get_visited() {
    return visited;
}

bool School::date_before(string date) {
    vector<string> this_data = utils::split_string(this->date, '.');
    vector<string> other_data = utils::split_string(date, '.');
    reverse(this_data.begin(), this_data.end());
    reverse(other_data.begin(), other_data.end());

    for(int i = 0;i < 3;i++){
        if(this_data[i] != other_data[i]){
            return this_data[i] < other_data[i];
        }
    }
    return false;
}

void School::set_visited(bool status) {
    this->visited = status;
}
