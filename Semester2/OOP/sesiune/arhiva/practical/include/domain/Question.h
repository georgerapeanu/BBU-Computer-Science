//
// Created by georgerapeanu on 11.06.2022.
//

#ifndef PRACTICAL_QUESTION_H
#define PRACTICAL_QUESTION_H

#include <string>
#include <iostream>

class Question{
    int id;
    std::string text;
    std::string user_name;
public:
    Question(int id, const std::string &text, const std::string &userName);

    int getId() const;

    const std::string &getText() const;

    void setText(const std::string &text);

    const std::string &getUserName() const;

    void setUserName(const std::string &userName);

    Question();

    bool operator==(const Question &rhs) const;

    bool operator!=(const Question &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Question &question);
    friend std::istream &operator>>(std::istream &is, Question &question);
};

#endif //PRACTICAL_QUESTION_H

