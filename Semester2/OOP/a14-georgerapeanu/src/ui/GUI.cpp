//
// Created by georgerapeanu on 07.05.2022.
//

#include "GUI.h"
#include <iostream>

GUI::GUI(MovieController &controller, QWidget *parent): controller(controller),QWidget(parent) {
   QVBoxLayout* mainLayout = new QVBoxLayout(this);
   this->loginAdminButton = new QPushButton("Login admin");
   this->loginUserButton = new QPushButton("Login user");
   this->adminGUI = new AdminGUI(controller);
   this->userGUI = new UserGUI(controller);
   mainLayout->addWidget(this->loginAdminButton);
   mainLayout->addWidget(this->loginUserButton);
   mainLayout->addWidget(this->adminGUI);
   mainLayout->addWidget(this->userGUI);
   this->adminGUI->hide();
   this->userGUI->hide();

   this->connect_stuff();
}

void GUI::connect_stuff() {
    QObject::connect(this->loginUserButton, &QPushButton::clicked, this, &GUI::handle_login_user_click);
    QObject::connect(this->loginAdminButton, &QPushButton::clicked, this, &GUI::handle_login_admin_click);
    QObject::connect(this->userGUI, &UserGUI::logout_clicked, this, &GUI::handle_logout_click);
    QObject::connect(this->adminGUI, &AdminGUI::logout_clicked, this, &GUI::handle_logout_click);
}

void GUI::handle_logout_click() {
    this->loginAdminButton->show();
    this->loginUserButton->show();
    this->userGUI->hide();
    this->adminGUI->hide();
}

void GUI::handle_login_user_click() {
    this->loginAdminButton->hide();
    this->loginUserButton->hide();
    this->userGUI->show();
    this->adminGUI->hide();
}

void GUI::handle_login_admin_click() {
    this->loginAdminButton->hide();
    this->loginUserButton->hide();
    this->userGUI->hide();
    this->adminGUI->show();
}
