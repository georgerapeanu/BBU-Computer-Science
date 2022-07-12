//
// Created by georgerapeanu on 07.04.2022.
//

#ifndef T1_SCHOOL_H
#define T1_SCHOOL_H

#include <string>

class School {
    std::string name;
    double lat;
    double lon;
    std::string date;
    bool visited;

public:
    School(std::string name, double lat, double lon, std::string date, bool visited);

    std::string get_name();

    double get_lat();

    double get_lon();

    std::string get_date();

    bool get_visited();

    /*!
     * @brief the setter for the schools visisted
     * @param status the new status of the school
     */
    void set_visited(bool status);

    bool date_before(std::string date);
};


#endif //T1_SCHOOL_H
