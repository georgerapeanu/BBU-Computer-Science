//
// Created by georgerapeanu on 11.06.2022.
//

#include "Controller.h"
#include "FileRepository.h"
#include "AppException.h"
#include <algorithm>
#include <map>


Controller::Controller(FileRepository <User> &users, FileRepository <Question> &questions,
                       FileRepository <Answer> &answers) : users(users), questions(questions), answers(answers) {
    ;
}

std::vector<Question> Controller::getQuestionsSortedDecreasinglyByAnswersCount() {
    std::vector<Answer> repo_answers = this->answers.getAll();
    std::map<int,int> answers_count;
    for(auto it:repo_answers){
        answers_count[it.getQuestionId()]++;
    }

    std::vector<Question> repo_questions = this->questions.getAll();
    sort(repo_questions.begin(), repo_questions.end(), [&answers_count](const Question& a, const Question& b){
        return answers_count[a.getId()] > answers_count[b.getId()];
    });

    return repo_questions;
}

std::vector<Answer> Controller::getAnswersForQuestionSortedDecreasinglyByVotes(const int question_id) {
    std::vector<Answer> repo_answers = this->answers.getAll();
    std::vector<Answer> accurate_answers;

    std::copy_if(repo_answers.begin(), repo_answers.end(), std::back_inserter(accurate_answers), [&question_id](const Answer& a){
        return a.getQuestionId() == question_id;
    });

    std::sort(accurate_answers.begin(), accurate_answers.end(), [](const Answer& fst, const Answer& snd){
        return fst.getVotes() > snd.getVotes();
    });

    return accurate_answers;
}

Question Controller::getBestMatchingQuestion(std::string &searchText) {
    int best_count = -1;
    Question best_question;
    for(auto question : this->questions.getAll()){
        int cnt = 0;
        for(int i = 0;i < (int)searchText.size() && i < question.getText().size();i++){
            cnt += (searchText[i] == question.getText()[i]);
        }
        if(cnt > best_count){
           best_count = cnt;
           best_question = question;
        }
    }
    return best_question;
}

void Controller::addQuestion(const User &user, const std::string &text) {
    if(text == ""){
        throw AppException("Question description cannot be empty");
    }
    this->questions.add(Question(this->questions.getAll().size(), text, user.getName()));
    this->notify();
}

void Controller::addAnswer(const User &user, const int question_id, const std::string &text) {
    if(text == ""){
        throw AppException("Question description cannot be empty");
    }
    this->answers.add(Answer(this->answers.getAll().size(), question_id, user.getName(), text, 0));
    this->notify();
}

void Controller::voteAnswer(const User &user, const int answer_id, int delta) {
    Answer tmp = this->answers.getById(Answer(answer_id, 0, "", "", 0));
    if(this->answers.getById(tmp).getAnsweringUserName() == user.getName()){
        throw AppException("User cannot vote his own answer");
    }
    tmp.setVotes(tmp.getVotes() + delta);
    this->answers.update(tmp);
    this->notify();
}

std::vector<User> Controller::getAllUsers() {
    return this->users.getAll();
}

