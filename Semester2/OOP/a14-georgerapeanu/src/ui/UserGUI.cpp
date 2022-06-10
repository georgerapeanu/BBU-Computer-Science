//
// Created by georgerapeanu on 18.05.2022.
//

#include "UserGUI.h"
#include "MovieController.h"
#include "Exceptions.h"

UserGUI::UserGUI(MovieController &controller, QWidget *parent): controller(controller), QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* appLayout = new QHBoxLayout();
    mainLayout->addLayout(appLayout);
    QVBoxLayout* leftLayout = new QVBoxLayout();
    QVBoxLayout* middleLayout = new QVBoxLayout();
    QVBoxLayout* rightLayout = new QVBoxLayout();
    appLayout->addLayout(leftLayout);
    appLayout->addLayout(middleLayout);
    appLayout->addLayout(rightLayout);

    this->currentGenre = "";
    this->getRepoMovies = [this, &controller](){
        return controller.get_movies_user(this->currentGenre);
    };

    this->getWatchlistMovies = [&controller](){
        return controller.get_watchlist_user();
    };

    ///LEFT setup
    this->moviesLabel = new QLabel("Movies:");
    leftLayout->addWidget(this->moviesLabel);
    this->movies_model = new MovieListModel(this->getRepoMovies);
    this->movies = new QTableView();
    this->movies->setModel(this->movies_model);
    leftLayout->addWidget(this->movies);

    QFormLayout* formLayout = new QFormLayout();
    leftLayout->addLayout(formLayout);

    this->genreTextField = new QLineEdit();
    formLayout->addRow(tr("&Genre:"),this->genreTextField);


    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    leftLayout->addLayout(buttonsLayout);

    this->moviesPlayButton = new QPushButton("Play");
    buttonsLayout->addWidget(this->moviesPlayButton);

    this->nextButton = new QPushButton("Next");
    buttonsLayout->addWidget(this->nextButton);

    ///MIDDLE setup

    this->transferButton = new QPushButton(">");
    middleLayout->addWidget(this->transferButton);

    ///RIGHT setup
    this->watchlistLabel = new QLabel("Watchlist:");
    rightLayout->addWidget(this->watchlistLabel);
    this->watchlist_model = new MovieListModel(this->getWatchlistMovies);
    this->watchlist = new QTableView();
    this->watchlist->setModel(this->watchlist_model);
    rightLayout->addWidget(this->watchlist);

    QHBoxLayout* playlistButtonsLayout = new QHBoxLayout();
    rightLayout->addLayout(playlistButtonsLayout);

    this->likeButton = new QPushButton("Like");
    playlistButtonsLayout->addWidget(this->likeButton);
    this->removeButton = new QPushButton("Remove");
    playlistButtonsLayout->addWidget(this->removeButton);
    this->displayWatchlistButton = new QPushButton("Display");
    playlistButtonsLayout->addWidget(this->displayWatchlistButton);
    this->displayNewWindowButton = new QPushButton("Display new window");
    playlistButtonsLayout->addWidget(this->displayNewWindowButton);

    this->errorMessageTextField = new QLineEdit();
    this->errorMessageTextField->setReadOnly(true);

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,QWidget::palette().color(QWidget::backgroundRole()));
    palette->setColor(QPalette::Text,Qt::red);
    this->errorMessageTextField->setPalette(*palette);
    this->errorMessageTextField->setFrame(false);
    mainLayout->addWidget(this->errorMessageTextField);

    this->logoutButton = new QPushButton("Logout");
    mainLayout->addWidget(this->logoutButton);

    this->connect_stuff();
    this->index = 0;
    this->watchlist_index = -1;
    this->reload_highlight();
}

void UserGUI::handle_genre_change(){
    std::string tmp = this->genreTextField->text().toStdString();
    this->movies_model->setMoviesFunction([this, tmp](){
        return controller.get_movies_matching_genre(tmp);
    });
    this->index = 0;
    this->movies_model->reload();
    this->reload_highlight();
}

void UserGUI::connect_stuff() {
    QObject::connect(this->genreTextField, &QLineEdit::textChanged, this, &UserGUI::handle_genre_change);
    QObject::connect(this->moviesPlayButton, &QPushButton::clicked, this, &UserGUI::handle_play);
    QObject::connect(this->nextButton, &QPushButton::clicked, this, &UserGUI::handle_next);
    QObject::connect(this->transferButton, &QPushButton::clicked, this, &UserGUI::handle_transfer);
    QObject::connect(this->likeButton, &QPushButton::clicked, this, &UserGUI::handle_like);
    QObject::connect(this->removeButton, &QPushButton::clicked, this, &UserGUI::handle_remove);
    QObject::connect(this->watchlist, &QTableView::clicked, this, &UserGUI::handle_watchlist_click);
    QObject::connect(this->logoutButton, &QPushButton::clicked, this, &UserGUI::handle_logout);
    QObject::connect(this->displayWatchlistButton, &QPushButton::clicked, this, &UserGUI::handle_display_watchlist);
    QObject::connect(this->displayNewWindowButton, &QPushButton::clicked, this, &UserGUI::handle_display_new_window);
}

void UserGUI::handle_play() {
    if(this->movies_model->rowCount() <= this->index || this->index < 0){
        return ;
    }
    system(("firefox " + this->getRepoMovies()[this->index].get_trailer_link()).c_str());
}

void UserGUI::handle_next() {
    this->index++;
    if(this->movies_model->rowCount() <= this->index || this->index < 0){
        this->index = 0;
    }
    this->reload_highlight();
}


void UserGUI::reload_highlight() {
    if(this->movies_model->rowCount() <= this->index || this->index < 0){
        return ;
    }
    this->movies->selectRow(this->index);
}

void UserGUI::handle_transfer() {
    if(this->movies_model->rowCount() <= this->index || this->index < 0){
        throw AppException("No movie selected");
    }
    try{
        this->controller.add_movie_user(this->getRepoMovies()[this->index]);
        this->errorMessageTextField->setText("");
    }catch(AppException &ex){
        this->errorMessageTextField->setText(ex.get_message().c_str());
    }
    this->watchlist_model->reload();
}

void UserGUI::handle_watchlist_click(const QModelIndex& index) {
    this->watchlist_index = index.row();
    this->watchlist->selectRow(index.row());
}

void UserGUI::handle_like() {
    try{
        if(this->watchlist_model->rowCount() <= this->watchlist_index || this->watchlist_index < 0){
            throw AppException("No movie selected");
        }
        this->controller.like_movie_user(this->getWatchlistMovies()[this->watchlist_index]);
        this->controller.remove_movie_user(this->getWatchlistMovies()[this->watchlist_index]);
        this->watchlist_index = -1;
        this->reload_highlight();
        this->watchlist_model->reload();
        this->movies_model->reload();
        this->errorMessageTextField->setText("");
    }catch(AppException &ex){
        this->errorMessageTextField->setText(ex.get_message().c_str());
    }
}

void UserGUI::handle_remove() {
    try{
        if(this->watchlist_model->rowCount() <= this->watchlist_index || this->watchlist_index < 0){
            throw AppException("No movie selected");
        }
        this->controller.remove_movie_user(this->getWatchlistMovies()[this->watchlist_index]);
        this->watchlist_index = -1;
        this->reload_highlight();
        this->errorMessageTextField->setText("");
        this->watchlist_model->reload();
    }catch(AppException &ex){
        this->errorMessageTextField->setText(ex.get_message().c_str());
    }
}

void UserGUI::handle_logout() {
    emit this->logout_clicked();
}

void UserGUI::show() {
    QWidget::show();
    this->movies_model->reload();
    this->watchlist_model->reload();
    this->reload_highlight();
}

void UserGUI::handle_display_watchlist() {
    this->controller.display_watchlist();
}

void UserGUI::handle_display_new_window() {
    QTableView* tmpView = new QTableView();
    tmpView->setModel(this->watchlist_model);
    tmpView->show();
}

