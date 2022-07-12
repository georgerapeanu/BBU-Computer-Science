//
// Created by georgerapeanu on 07.05.2022.
//

#ifndef A11_12_GEORGERAPEANU_MAINWINDOW_H
#define A11_12_GEORGERAPEANU_MAINWINDOW_H

#include <QtWidgets>
#include "MovieController.h"
#include "MovieListModel.h"
#include "AdminGUI.h"
#include "UserGUI.h"

class GUI: public QWidget{
    Q_OBJECT
private:
    MovieController& controller;
    void connect_stuff();

protected:
    std::string currentGenre;
    std::function<std::vector<Movie>()> getRepoMovies;
    std::function<std::vector<Movie>()> getWatchlistMovies;
public:
    GUI(MovieController &controller, QWidget* parent = Q_NULLPTR);

    QPushButton* loginUserButton;
    QPushButton* loginAdminButton;
    AdminGUI* adminGUI;
    UserGUI* userGUI;

public slots:
    void handle_logout_click();
    void handle_login_user_click();
    void handle_login_admin_click();
};


#endif //A11_12_GEORGERAPEANU_MAINWINDOW_H
