//
// Created by georgerapeanu on 11.06.2022.
//

#include "User.h"

User::User(const std::string &name) : name(name) {}

const std::string &User::getName() const {
    return name;
}

void User::setName(const std::string &name) {
    User::name = name;
}

std::ostream &operator<<(std::ostream &os, const User &user) {
    os << user.name;
    return os;
}

std::istream &operator>>(std::istream &is, User &user) {
    is >> user.name;
    return is;
}

std::string User::getId() const {
    return this->getName();
}

User::User() {}
