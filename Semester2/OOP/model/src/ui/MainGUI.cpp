//
// Created by georgerapeanu on 08.06.2022.
//

#include "MainGUI.h"
#include "ProgrammerWindow.h"
#include "TesterWindow.h"

MainGUI::MainGUI(IssueController &issue_controller, UserController &user_controller) : issue_controller(issue_controller), user_controller(user_controller) {
    IssuesModel* model = new IssuesModel(issue_controller);
    for(auto &it:user_controller.getAll()){
        if(it.getType() == "programmer"){
            ProgrammerWindow* window = new ProgrammerWindow(it, *model);
            window->show();
        }else{
            TesterWindow* window = new TesterWindow(it, *model);
            window->show();
        }
    }
}
