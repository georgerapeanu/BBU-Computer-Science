//
// Created by georgerapeanu on 09.06.2022.
//

#include "Question.h"

int Question::getId() const {
    return id;
}

const std::string &Question::getText() const {
    return text;
}

const std::string &Question::getCorrectAnswer() const {
    return correct_answer;
}

int Question::getScore() const {
    return score;
}


Question::Question(int id, const std::string &text, const std::string &correctAnswer, int score) : id(id), text(text),
                                                                                                   correct_answer(
                                                                                                           correctAnswer),
                                                                                                   score(score) {}

std::ostream &operator<<(std::ostream &os, const Question &question) {
    os << question.id << "  " << question.text << " " << question.correct_answer << " " << question.score;
    return os;
}

std::istream& operator >> (std::istream& is, Question &question){
    is >> question.id >> question.text >> question.correct_answer >> question.score;
    return is;
}

bool Question::operator==(const Question &rhs) const {
    return id == rhs.id;
}

bool Question::operator!=(const Question &rhs) const {
    return !(rhs == *this);
}

Question::Question() {
    ;
}
