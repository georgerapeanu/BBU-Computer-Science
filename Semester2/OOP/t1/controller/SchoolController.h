//
// Created by georgerapeanu on 07.04.2022.
//

#ifndef T1_SCHOOLCONTROLLER_H
#define T1_SCHOOLCONTROLLER_H

#include "School.h"
#include "SchoolRepository.h"
#include <string>
#include <vector>

class SchoolController {
    SchoolRepository repository;
public:
    SchoolController();
    void add_school(std::string name, double lat, double lon, std::string date, bool visited);
    /*!
     * @brief this function removes a school, given its name and address
     * @param name the name of the school
     * @param lat the latitude of the school
     * @param lon the longitude of the school
     */
    void remove_school(std::string name, double lat, double lon);
    std::vector<School> get_all_schools_sorted_by_name();
    /*!
     * @brief this function marks all schools as visited before a given date
     * @param date the date
     */
    void mark_all_schools_as_visited_before_date(std::string date);
    std::vector<School> get_all_schools_unvisited_after_date(std::string date);
};


#endif //T1_SCHOOLCONTROLLER_H
