//
// Created by georgerapeanu on 11.06.2022.
//

#ifndef PRACTICAL_USER_H
#define PRACTICAL_USER_H

#include <string>
#include <iostream>

class User{
    std::string name;
public:
    const std::string &getName() const;

    void setName(const std::string &name);

    std::string getId() const ;

public:
    friend std::ostream &operator<<(std::ostream &os, const User &user);
    friend std::istream &operator>>(std::istream &is, User &user);

    User(const std::string &name);

    User();
};

#endif //PRACTICAL_USER_H
