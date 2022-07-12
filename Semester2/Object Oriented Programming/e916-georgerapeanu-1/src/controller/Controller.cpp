//
// Created by georgerapeanu on 12.06.2022.
//

#include "Controller.h"
#include "AppException.h"

#include <map>
#include <algorithm>

Controller::Controller(GenericFileRepository<User> &users, GenericFileRepository<Question> &questions,
                       GenericFileRepository<Answer> &answers) : users(users), questions(questions), answers(answers) {}

std::vector<Question> Controller::getAllQuestionsSortedDecreasinglyByAnswerCount() {
    std::vector<Answer> repo_answers = this->answers.getAll();
    std::map<int, int> answer_count;

    for(auto it:this->answers.getAll()){
        answer_count[it.getQuestionId()]++;
    }

    std::vector<Question> repo_questions = this->questions.getAll();
    std::sort(repo_questions.begin(), repo_questions.end(), [&](const Question& fst, const Question& snd){
        return answer_count[fst.getId()] > answer_count[snd.getId()];
    });

    return repo_questions;
}

Question Controller::getBestMatchingQuestion(std::string search_text) {
    Question answer;
    int best_score = -1;

    for(const auto &question:this->questions.getAll()){
        int local_score = 0;
        for(int i = 0; i < (int)question.getText().size() && i < (int)search_text.size();i++){
            local_score += (question.getText()[i] == search_text[i]);
        }
        if(best_score < local_score){
            best_score = local_score;
            answer = question;
        }
    }

    return answer;
}

std::vector<Answer> Controller::getAnswersForQuestionSortedDecreasinglyByVotes(int question_id) {
    std::vector<Answer> repo_answers = this->answers.getAll();
    std::vector<Answer> relevant_answers;
    std::copy_if(repo_answers.begin(), repo_answers.end(), std::back_inserter(relevant_answers), [&question_id](const Answer& answer){
       return answer.getQuestionId() == question_id;
    });
    std::sort(relevant_answers.begin(), relevant_answers.end(), [](const Answer &fst, const Answer &snd){
       return fst.getNumberOfVotes() > snd.getNumberOfVotes();
    });
    return relevant_answers;
}

void Controller::addQuestion(const User &user, std::string question_text) {
    if(question_text == ""){
        throw AppException("Question text cannot be empty");
    }
    this->questions.add(Question((int)this->questions.getAll().size(), question_text, user.getName()));
    this->notify();
}

void Controller::addAnswer(const User &user, int question_id, std::string answer_text) {
    if(answer_text == ""){
        throw AppException("Answer cannot be empty");
    }
    this->answers.add(Answer((int)this->answers.getAll().size(), question_id, user.getName(), answer_text, 0));
    this->notify();
}

void Controller::voteAnswer(const User &user, int answer_id, int delta) {
    Answer answer = this->answers.getById(Answer(answer_id, 0, "", "", 0));
    if(user.getName() == answer.getAnsweringName()){
        throw AppException("User cannot vote his own answer");
    }
    answer.setNumberOfVotes(answer.getNumberOfVotes() + delta);
    this->answers.update(answer);
    this->notify();
}

std::vector<User> Controller::getAllUsers() const {
    return this->users.getAll();
}
