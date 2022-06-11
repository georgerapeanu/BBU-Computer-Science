//
// Created by georgerapeanu on 11.06.2022.
//

#include "Answer.h"
#include "AppException.h"
#include <vector>
#include <sstream>

Answer::Answer(int id, int questionId, const std::string &answeringUserName, const std::string &answerText, int votes)
        : id(id), question_id(questionId), answering_user_name(answeringUserName), answer_text(answerText),
          votes(votes) {}

int Answer::getId() const {
    return id;
}

int Answer::getQuestionId() const {
    return question_id;
}

void Answer::setQuestionId(int questionId) {
    question_id = questionId;
}

const std::string &Answer::getAnsweringUserName() const {
    return answering_user_name;
}

void Answer::setAnsweringUserName(const std::string &answeringUserName) {
    answering_user_name = answeringUserName;
}

const std::string &Answer::getAnswerText() const {
    return answer_text;
}

void Answer::setAnswerText(const std::string &answerText) {
    answer_text = answerText;
}

int Answer::getVotes() const {
    return votes;
}

void Answer::setVotes(int votes) {
    Answer::votes = votes;
}

std::ostream &operator<<(std::ostream &os, const Answer &answer) {
    os << answer.id << "~" << answer.question_id << "~" << answer.answering_user_name << "~" << answer.answer_text << "~" << answer.votes;
    return os;
}

std::istream &operator>>(std::istream &is, Answer &answer) {
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

    if(parts.size() != 5){
        throw AppException("Invalid line for answer");
    }

    std::istringstream id_stream(parts[0]), question_stream(parts[1]), answering_username_stream(parts[2]), answer_text_stream(parts[3]), votes_stream(parts[4]);

    id_stream >> answer.id;
    question_stream >> answer.question_id;
    answering_username_stream >> answer.answering_user_name;
    answer_text_stream >> answer.answer_text;
    votes_stream >> answer.votes;

    return is;
}

Answer::Answer() {}