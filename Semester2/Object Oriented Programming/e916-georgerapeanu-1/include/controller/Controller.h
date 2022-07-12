//
// Created by georgerapeanu on 12.06.2022.
//

#ifndef E916_GEORGERAPEANU_1_CONTROLLER_H
#define E916_GEORGERAPEANU_1_CONTROLLER_H

#include "AbstractSubject.h"
#include "GenericFileRepository.h"
#include "User.h"
#include "Question.h"
#include "Answer.h"
#include <vector>

class Controller : public AbstractSubject{
    GenericFileRepository<User>& users;
    GenericFileRepository<Question>& questions;
    GenericFileRepository<Answer>& answers;

public:

    Controller(GenericFileRepository<User> &users, GenericFileRepository<Question> &questions,
               GenericFileRepository<Answer> &answers);

    std::vector<Question> getAllQuestionsSortedDecreasinglyByAnswerCount();
    Question getBestMatchingQuestion(std::string search_text);
    std::vector<Answer> getAnswersForQuestionSortedDecreasinglyByVotes(int question_id);
    void addQuestion(const User& user, std::string question_text);
    void addAnswer(const User& user, int question_id, std::string answer_text);
    void voteAnswer(const User& user, int answer_id, int delta);
    std::vector<User> getAllUsers()const;
};

#endif //E916_GEORGERAPEANU_1_CONTROLLER_H
