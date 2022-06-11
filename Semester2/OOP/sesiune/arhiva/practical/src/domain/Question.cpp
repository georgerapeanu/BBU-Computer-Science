//
// Created by georgerapeanu on 11.06.2022.
//

#include <string>
#include "Question.h"
#include "AppException.h"
#include <sstream>
#include <vector>

Question::Question(int id, const std::string &text,
                   const std::string &userName) : id(id), text(text), user_name(userName) {}

int Question::getId() const {
    return id;
}

const std::string &Question::getText() const {
    return text;
}

void Question::setText(const std::string &text) {
    Question::text = text;
}

const std::string &Question::getUserName() const {
    return user_name;
}

void Question::setUserName(const std::string &userName) {
    user_name = userName;
}


std::ostream &operator<<(std::ostream &os, const Question &question) {
    os << question.id << "~" << question.text << "~" << question.user_name;
    return os;
}

std::istream &operator>>(std::istream &is, Question &question) {
    std::string line;
    std::getline(is, line);

    if(line == ""){
        return is;
    }

    std::vector<std::string> parts;

    parts.push_back("");

    for(auto it:line){
        if(it == '~'){
            parts.push_back("");
            continue;
        }
        parts.back() += it;
    }

    if(parts.size() != 3){
        throw AppException("Invalid line for question");
    }

    std::istringstream id_stream(parts[0]), text_stream(parts[1]), user_stream(parts[2]);

    id_stream >> question.id;
    text_stream >> question.text;
    user_stream >> question.user_name;

    return is;
}

Question::Question() {}

bool Question::operator==(const Question &rhs) const {
    return id == rhs.id &&
           text == rhs.text &&
           user_name == rhs.user_name;
}

bool Question::operator!=(const Question &rhs) const {
    return !(rhs == *this);
}
