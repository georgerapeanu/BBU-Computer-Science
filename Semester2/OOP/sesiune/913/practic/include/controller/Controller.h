//
// Created by georgerapeanu on 09.06.2022.
//

#ifndef PRACTIC_CONTROLLER_H
#define PRACTIC_CONTROLLER_H

#include "GenericFileRepository.h"
#include "Participant.h"
#include "Question.h"
#include <vector>
#include <map>
#include "AbstractSubject.h"

class Controller : public AbstractSubject{
    GenericFileRepository<Participant>& participants;
    GenericFileRepository<Question>& questions;

public:
    Controller(GenericFileRepository<Participant> &participants, GenericFileRepository<Question> &questions);

    std::vector<Question> getQuestionsSortedById();
    std::vector<Question> getQuestionsSortedByScoreDescendingly();
    void addQuestion(int id, const std::string& text, const std::string& answer, int score);
    void answerQuestion(const Participant& participant, int id, const std::string &answer);
    Participant getUpdatedParticipant(const Participant& participant);
    std::vector<Participant> getAllParticipants();
};

#endif //PRACTIC_CONTROLLER_H
