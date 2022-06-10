//
// Created by georgerapeanu on 09.06.2022.
//

#ifndef PRACTIC_QUESTION_H
#define PRACTIC_QUESTION_H

#include <string>
#include <iostream>

class Question{
    int id;
    std::string text;
    std::string correct_answer;
    int score;
public:
    Question(int id, const std::string &text, const std::string &correctAnswer, int score);
    Question();

    int getId() const;

    const std::string &getText() const;

    const std::string &getCorrectAnswer() const;

    int getScore() const;

    friend std::istream& operator >> (std::istream& is, Question& question);

    friend std::ostream &operator<<(std::ostream &os, const Question &question);

    bool operator==(const Question &rhs) const;

    bool operator!=(const Question &rhs) const;
};

#endif //PRACTIC_QUESTION_H
