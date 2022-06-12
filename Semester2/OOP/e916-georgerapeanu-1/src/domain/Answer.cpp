//
// Created by georgerapeanu on 12.06.2022.
//

#include "Answer.h"
#include "AppException.h"
#include <vector>
#include <sstream>

Answer::Answer(int id, int questionId, const std::string &answeringName, const std::string &text, int numberOfVotes)
        : id(id), question_id(questionId), answering_name(answeringName), text(text), number_of_votes(numberOfVotes) {}


int Answer::getQuestionId() const {
    return question_id;
}

void Answer::setQuestionId(int questionId) {
    question_id = questionId;
}

const std::string &Answer::getAnsweringName() const {
    return answering_name;
}

void Answer::setAnsweringName(const std::string &answeringName) {
    answering_name = answeringName;
}

const std::string &Answer::getText() const {
    return text;
}

void Answer::setText(const std::string &text) {
    Answer::text = text;
}

int Answer::getNumberOfVotes() const {
    return number_of_votes;
}

void Answer::setNumberOfVotes(int numberOfVotes) {
    number_of_votes = numberOfVotes;
}

int Answer::getId() const {
    return id;
}

std::ostream &operator<<(std::ostream &os, const Answer &answer) {
    os << answer.id << "|" << answer.question_id << "|" << answer.answering_name << "|" << answer.text << "|" << answer.number_of_votes;
    return os;
}

std::istream &operator>>(std::istream &is, Answer &answer){
    std::string line;
    std::getline(is, line);

    if(line == ""){
        return is;
    }

    std::vector<std::string> parts = {""};

    for(auto it:line){
        if(it == '|'){
            parts.push_back("");
        }else{
            parts.back() += it;
        }
    }

    if(parts.size() != 5){
        throw AppException("Invalid line for answer");
    }

    std::istringstream id_stream(parts[0]), question_id_stream(parts[1]), answering_name_stream(parts[2]), text_stream(parts[3]), votes_stream(parts[4]);

    id_stream >> answer.id;
    question_id_stream >> answer.question_id;
    std::string tmp = "";
    answer.answering_name = "";
    while(answering_name_stream >> tmp){
        if(answer.answering_name.size() > 0){
            answer.answering_name += " ";
        }
        answer.answering_name += tmp;
    }
    tmp = "";
    answer.text = "";
    while(text_stream >> tmp){
        if(answer.text.size() > 0){
            answer.text += " ";
        }
        answer.text += tmp;
    }
    votes_stream >> answer.number_of_votes;

    return is;
}

Answer::Answer() {}
