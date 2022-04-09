//
// Created by georgerapeanu on 07.04.2022.
//

#ifndef T1_SCHOOLREPOSITORY_H
#define T1_SCHOOLREPOSITORY_H

#include "School.h"
#include <vector>

class SchoolRepository {
    std::vector<School> schools;
public:
    SchoolRepository();
    void add_school(School school);
    /*!
     * @brief this function removes a school
     * For this, a "dummy" school is provided, which has the same name and address as the one to be removed
     * @param school the dummy school
     * @raises AppException if no such school exists
     */
    void remove_school(School school);
    /*!
     * @brief this function marks a school as visited
     * For this, a "dummy" school is provided, which has the same name and address as the one to be removed
     * @param school the dummy school
     * @raises AppException if no such school exists
     */
    void mark_school_as_visited(School school);
    std::vector<School> get_all_schools();
};


#endif //T1_SCHOOLREPOSITORY_H
