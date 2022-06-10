//
// Created by georgerapeanu on 09.06.2022.
//

#include "Participant.h"
#include <iostream>

Participant::Participant(const std::string &name, int score) : name(name), score(score) {}

const std::string &Participant::getName() const {
    return name;
}

bool Participant::operator==(const Participant &rhs) const {
    return this->name == rhs.name;
}

bool Participant::operator!=(const Participant &rhs) const {
    return !(rhs == *this);
}

int Participant::getScore() const {
    return score;
}

Participant::Participant() {
    ;
}

std::istream &operator>>(std::istream &is, Participant &participant) {
    is >> participant.name;
    is >> participant.score;
    return is;
}

std::ostream &operator<<(std::ostream &os, const Participant &participant) {
    os << participant.name << " " << participant.score;
    return os;
}
