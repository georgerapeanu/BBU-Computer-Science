//
// Created by georgerapeanu on 09.06.2022.
//
#include <QApplication>
#include "ParticipantWindow.h"
#include "Controller.h"
#include "GenericFileRepository.h"
#include "Participant.h"
#include "Question.h"
#include "GUIManager.h"


int main(int argc, char** argv){

    QApplication app(argc, argv);

    GenericFileRepository<Participant> participants("participants.txt");
    GenericFileRepository<Question> questions("./questions.txt");

    Controller controller(participants, questions);

    GUIManager manager(controller);

    return app.exec();
}
