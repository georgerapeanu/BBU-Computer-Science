//
// Created by georgerapeanu on 09.06.2022.
//

#include <algorithm>
#include "Controller.h"
#include "AppException.h"

Controller::Controller(GenericFileRepository<Participant> &participants, GenericFileRepository<Question> &questions)
        : participants(participants), questions(questions) {
}

std::vector<Question> Controller::getQuestionsSortedById() {
    std::vector<Question> repo_questions = this->questions.getAll();
    std::sort(repo_questions.begin(), repo_questions.end(), [](const Question& a, const Question& b){
        return a.getId() < b.getId();
    });
    return repo_questions;
}

std::vector<Question> Controller::getQuestionsSortedByScoreDescendingly() {
    std::vector<Question> repo_questions = this->questions.getAll();
    std::sort(repo_questions.begin(), repo_questions.end(), [](const Question& a, const Question& b){
        return a.getScore() > b.getScore();
    });
    return repo_questions;
}

void Controller::addQuestion(int id, const std::string &text, const std::string &answer, int score) {
    if(text == ""){
        throw AppException("Question text can't be empty");
    }
    Question question(id, text, answer, score);
    this->questions.add(question);
    this->notify();
}

void Controller::answerQuestion(const Participant &participant, int id, const std::string &answer) {
    Question question;
    bool found = false;
    for(auto it:this->questions.getAll()){
        if(it.getId() == id){
            question = it;
            found = true;
            break;
        }
    }
    if(!found){
        throw AppException("Question with specified id doesn't exist!");
    }
    if(question.getCorrectAnswer() != answer){
        return ;
    }
    this->participants.update(Participant(participant.getName(), participant.getScore() + question.getScore()));
    this->notify();
}

Participant Controller::getUpdatedParticipant(const Participant &participant) {
    for(auto &it:this->participants.getAll()){
        if(participant == it){
            return it;
        }
    }
    throw AppException("No such participant exists");
}

std::vector<Participant> Controller::getAllParticipants() {
    return this->participants.getAll();
}

