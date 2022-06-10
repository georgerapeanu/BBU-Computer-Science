//
// Created by georgerapeanu on 09.06.2022.
//

#ifndef PRACTIC_PARTICIPANT_H
#define PRACTIC_PARTICIPANT_H

#include <string>

class Participant{
    std::string name;
    int score;
public:
    Participant(const std::string &name, int score);
    Participant();

public:

    const std::string &getName() const;

    int getScore() const;

    bool operator==(const Participant &rhs) const;

    bool operator!=(const Participant &rhs) const;

    friend std::istream& operator >> (std::istream& is, Participant &participant);

    friend std::ostream& operator << (std::ostream& os, const Participant &participant);
};

#endif //PRACTIC_PARTICIPANT_H
