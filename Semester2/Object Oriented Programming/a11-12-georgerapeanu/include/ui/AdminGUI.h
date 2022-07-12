//
// Created by georgerapeanu on 18.05.2022.
//

#ifndef A11_12_GEORGERAPEANU_ADMINGUI_H
#define A11_12_GEORGERAPEANU_ADMINGUI_H
#include <QtWidgets>
#include "MovieController.h"
#include "MovieList.h"

class AdminGUI: public QWidget{
    Q_OBJECT
private:
    MovieController& controller;
protected:
    std::function<std::vector<Movie>()> getRepoMovies;
public:

    AdminGUI(MovieController &controller, QWidget* parent = Q_NULLPTR);

    virtual void show();

    QLabel* moviesLabel;

    MovieList* movies;

    QLineEdit* titleTextField;
    QLineEdit* genreTextField;
    QLineEdit* yearTextField;
    QLineEdit* likesTextField;
    QLineEdit* trailerTextField;

    QPushButton* addButton;
    QPushButton* updateButton;
    QPushButton* removeButton;
    QLineEdit* errorMessageTextField;
    QPushButton* logoutButton;

    void connect_stuff();

public slots:
    void handle_add();
    void handle_remove();
    void handle_update();
    void handle_movie_click(int x);
    void handle_logout();

private:
    void fetch_data(std::string &title, std::string &genre, int& year, int& likes, std::string& trailer);

signals:
    void logout_clicked();
};


#endif //A11_12_GEORGERAPEANU_ADMINGUI_H
