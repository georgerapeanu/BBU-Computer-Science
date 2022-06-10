//
// Created by georgerapeanu on 18.05.2022.
//

#ifndef A11_12_GEORGERAPEANU_USERGUI_H
#define A11_12_GEORGERAPEANU_USERGUI_H

#include <QtWidgets>
#include "MovieController.h"
#include "MovieListModel.h"

class UserGUI: public QWidget{
    Q_OBJECT
private:
    MovieController& controller;
protected:
    std::string currentGenre;
    std::function<std::vector<Movie>()> getRepoMovies;
    std::function<std::vector<Movie>()> getWatchlistMovies;
    int index;
    void connect_stuff();
    int watchlist_index;


public slots:
    void handle_genre_change();
    void reload_highlight();
    void handle_play();
    void handle_next();
    void handle_transfer();

    void handle_like();
    void handle_remove();
    void handle_watchlist_click(const QModelIndex &index);
    void handle_logout();

    void handle_display_watchlist();
    void handle_display_new_window();

public:
    UserGUI(MovieController &controller, QWidget* parent = Q_NULLPTR);

    virtual void show();

    QLabel* moviesLabel;
    QLabel* watchlistLabel;

    MovieListModel* movies_model;

    MovieListModel* watchlist_model;

    QTableView* movies;
    QTableView* watchlist;

    QLineEdit* genreTextField;
    QPushButton* moviesPlayButton;
    QPushButton* transferButton;
    QPushButton* nextButton;

    QPushButton* likeButton;
    QPushButton* removeButton;
    QPushButton* displayWatchlistButton;
    QPushButton* displayNewWindowButton;

    QLineEdit* errorMessageTextField;

    QPushButton* logoutButton;

signals:
    void logout_clicked();
};

#endif //A11_12_GEORGERAPEANU_USERGUI_H
