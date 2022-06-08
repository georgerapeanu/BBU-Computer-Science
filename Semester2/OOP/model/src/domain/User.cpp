//
// Created by georgerapeanu on 08.06.2022.
//

#include "User.h"
#include <iostream>

User::User(const std::string &name, const std::string &type):name(name), type(type) {
    ;
}

const std::string User::getId() const {
    return "";
}

const std::string &User::getName() const {
    return this->name;
}

void User::setName(const std::string &name) {
    this->name = name;
}

const std::string &User::getType() const {
    return this->type;
}

void User::setType(const std::string &type) {
    this->type = type;
}

std::istream &operator>>(std::istream &stream, User &user) {
    stream >> user.name >> user.type;
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const User &user) {
    stream << user.name << " " << user.type;
    return stream;
}

bool User::operator==(const User &other) const {
    return false;
}

User::User() {
    ;
}
