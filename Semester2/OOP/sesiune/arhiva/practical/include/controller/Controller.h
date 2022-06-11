//
// Created by georgerapeanu on 11.06.2022.
//

#ifndef PRACTICAL_CONTROLLER_H
#define PRACTICAL_CONTROLLER_H

#include "User.h"
#include "Question.h"
#include "Answer.h"
#include "FileRepository.h"
#include "AbstractSubject.h"

#include <vector>

class Controller : public AbstractSubject{
    FileRepository<User>& users;
    FileRepository<Question>& questions;
    FileRepository<Answer>& answers;
public:
    Controller(FileRepository<User> &users, FileRepository<Question> &questions, FileRepository<Answer> &answers);

public:

    std::vector<Question> getQuestionsSortedDecreasinglyByAnswersCount();
    std::vector<Answer> getAnswersForQuestionSortedDecreasinglyByVotes(const int question_id);
    Question getBestMatchingQuestion(std::string& searchText);
    void addQuestion(const User &user, const std::string& text);
    void addAnswer(const User &user, const int question_id, const std::string& text);
    void voteAnswer(const User& user, const int answer_id, int delta);

    std::vector<User> getAllUsers();
};

#endif //PRACTICAL_CONTROLLER_H
