//
// Created by georgerapeanu on 12.06.2022.
//

#ifndef E916_GEORGERAPEANU_1_USER_H
#define E916_GEORGERAPEANU_1_USER_H

#include <string>
#include <iostream>

class User{
    std::string name;
public:
    User(const std::string &name);

    const std::string &getName() const;

    void setName(const std::string &name);

    User();

    std::string getId() const;

    friend std::ostream &operator<<(std::ostream &os, const User &user);

    friend std::istream &operator>>(std::istream &is, User &user);
};


#endif //E916_GEORGERAPEANU_1_USER_H
