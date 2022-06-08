//
// Created by georgerapeanu on 08.06.2022.
//

#ifndef MODEL_MAINGUI_H
#define MODEL_MAINGUI_H

#include <QtWidgets>
#include "IssueController.h"
#include "UserController.h"

class MainGUI:public QWidget{
    Q_OBJECT

    IssueController &issue_controller;
    UserController &user_controller;

public:
    MainGUI(IssueController &issue_controller, UserController &user_controller);
};

#endif //MODEL_MAINGUI_H
