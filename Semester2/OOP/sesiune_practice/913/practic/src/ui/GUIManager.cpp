//
// Created by georgerapeanu on 09.06.2022.
//

#ifndef PRACTIC_GUIMANAGER_CPP
#define PRACTIC_GUIMANAGER_CPP

#include "GUIManager.h"
#include "ParticipantWindow.h"
#include "PresenterWindow.h"

#endif //PRACTIC_GUIMANAGER_CPP

GUIManager::GUIManager(Controller &controller) {
    PresenterWindow* presenter = new PresenterWindow(controller);
    presenter->show();
    for(auto it:controller.getAllParticipants()){
        ParticipantWindow* participant = new ParticipantWindow(it, controller);
        participant->show();
    }
}
