//
// Created by georgerapeanu on 18.05.2022.
//

#ifndef A11_12_GEORGERAPEANU_ADMINGUI_H
#define A11_12_GEORGERAPEANU_ADMINGUI_H
#include <QtWidgets>
#include "MovieController.h"
#include "MovieListModel.h"


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

    QTableView* movies;
    MovieListModel* movies_model;

    QLineEdit* titleTextField;
    QLineEdit* genreTextField;
    QLineEdit* yearTextField;
    QLineEdit* likesTextField;
    QLineEdit* trailerTextField;

    QPushButton* addButton;
    QPushButton* updateButton;
    QPushButton* removeButton;

    QPushButton* undoButton;
    QPushButton* redoButton;

    QLineEdit* errorMessageTextField;
    QPushButton* logoutButton;

    void connect_stuff();

public slots:
    void handle_add();
    void handle_remove();
    void handle_update();
    void handle_movie_click(const QModelIndex &index);
    void handle_logout();
    void handle_undo();
    void handle_redo();

private:
    void fetch_data(std::string &title, std::string &genre, int& year, int& likes, std::string& trailer);

signals:
    void logout_clicked();
};


#endif //A11_12_GEORGERAPEANU_ADMINGUI_H
