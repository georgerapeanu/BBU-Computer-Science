//
// Created by georgerapeanu on 12.06.2022.
//

#ifndef E916_GEORGERAPEANU_1_QUESTION_H
#define E916_GEORGERAPEANU_1_QUESTION_H

#include <string>
#include <ostream>

class Question{
    int id;
public:
    int getId() const;

public:
    Question();

    friend std::ostream &operator<<(std::ostream &os, const Question &question);

    bool operator==(const Question &rhs) const;

    bool operator!=(const Question &rhs) const;

    friend std::istream &operator>>(std::istream &is, Question &question);

    const std::string &getText() const;

    void setText(const std::string &text);

    const std::string &getUserName() const;

    void setUserName(const std::string &userName);

public:
    Question(int id, const std::string &text, const std::string &userName);

private:
    std::string text;
    std::string user_name;

};

#endif //E916_GEORGERAPEANU_1_QUESTION_H
