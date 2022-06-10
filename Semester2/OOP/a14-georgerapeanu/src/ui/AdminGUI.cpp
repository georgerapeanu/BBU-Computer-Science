//
// Created by georgerapeanu on 18.05.2022.
//

#include "AdminGUI.h"
#include "Exceptions.h"

using namespace std;

AdminGUI::AdminGUI(MovieController &controller, QWidget *parent): controller(controller), QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);


    this->getRepoMovies = [this, &controller](){
        return controller.get_all_movies_admin();
    };

    ///LEFT setup
    this->moviesLabel = new QLabel("Movies:");
    mainLayout->addWidget(this->moviesLabel);
    this->movies_model = new MovieListModel(this->getRepoMovies);
    this->movies = new QTableView();
    this->movies->setModel(this->movies_model);
    mainLayout->addWidget(this->movies);

    QFormLayout* formLayout = new QFormLayout();
    mainLayout->addLayout(formLayout);
    this->titleTextField = new QLineEdit();
    formLayout->addRow(tr("&Title:"),this->titleTextField);

    this->genreTextField = new QLineEdit();
    formLayout->addRow(tr("&Genre:"),this->genreTextField);

    this->yearTextField = new QLineEdit();
    formLayout->addRow(tr("&Year:"),this->yearTextField);

    this->likesTextField = new QLineEdit();
    formLayout->addRow(tr("&Likes:"),this->likesTextField);

    this->trailerTextField = new QLineEdit();
    formLayout->addRow(tr("&Trailer:"),this->trailerTextField);

    QVBoxLayout* buttonsLayout = new QVBoxLayout();
    mainLayout->addLayout(buttonsLayout);

    QHBoxLayout* CRUDButtonsLayout = new QHBoxLayout();
    buttonsLayout->addLayout(CRUDButtonsLayout);

    this->addButton = new QPushButton("Add");
    CRUDButtonsLayout->addWidget(this->addButton);
    this->updateButton = new QPushButton("Update");
    CRUDButtonsLayout->addWidget(this->updateButton);
    this->removeButton = new QPushButton("Remove");
    CRUDButtonsLayout->addWidget(this->removeButton);

    QHBoxLayout* undoButtonsLayout = new QHBoxLayout();
    buttonsLayout->addLayout(undoButtonsLayout);
    this->undoButton = new QPushButton("Undo");
    undoButtonsLayout->addWidget(this->undoButton);
    this->redoButton = new QPushButton("Redo");
    undoButtonsLayout->addWidget(this->redoButton);

    this->errorMessageTextField = new QLineEdit();
    this->errorMessageTextField->setReadOnly(true);

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,QWidget::palette().color(QWidget::backgroundRole()));
    palette->setColor(QPalette::Text,Qt::red);
    /*
    QLinearGradient linearGrad(QPointF(0, 0), QPointF(this->width(), this->height()));
    linearGrad.setSpread(QGradient::RepeatSpread);
    linearGrad.setColorAt(0, Qt::black);
    linearGrad.setColorAt(1, Qt::white);
    QBrush brush(linearGrad);

    palette->setBrush(QPalette::Base, brush);
    palette->setBrush(QPalette::Highlight, brush);
    palette->setBrush(QPalette::HighlightedText, brush);
     */
    this->errorMessageTextField->setPalette(*palette);

    this->errorMessageTextField->setFrame(false);
    mainLayout->addWidget(this->errorMessageTextField);

    this->logoutButton = new QPushButton("Logout");
    mainLayout->addWidget(logoutButton);
    this->connect_stuff();
}

void AdminGUI::connect_stuff() {
    QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::handle_add);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::handle_update);
    QObject::connect(this->removeButton, &QPushButton::clicked, this, &AdminGUI::handle_remove);
    QObject::connect(this->logoutButton, &QPushButton::clicked, this, &AdminGUI::handle_logout);
    QObject::connect(this->movies, &QTableView::clicked, this, &AdminGUI::handle_movie_click);
    QObject::connect(this->undoButton, &QPushButton::clicked, this, &AdminGUI::handle_undo);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &AdminGUI::handle_redo);

    QShortcut* undo_shortcut = new QShortcut(QKeySequence(tr("CTRL+Z")), this->undoButton);
    QObject::connect(undo_shortcut, &QShortcut::activated, this, &AdminGUI::handle_undo);
    QShortcut* redo_shortcut = new QShortcut(QKeySequence(tr("CTRL+Y")), this->redoButton);
    QObject::connect(redo_shortcut, &QShortcut::activated, this, &AdminGUI::handle_redo);
}

void AdminGUI::handle_add() {
    try{
        string title;
        string genre;
        string trailer;
        int likes;
        int year;
        this->fetch_data(title, genre, year, likes, trailer);
        this->controller.add_movie_admin(title, genre, year, likes, trailer);
        this->movies_model->reload();
        this->errorMessageTextField->setText("");
    }catch (const AppException& exception){
        this->errorMessageTextField->setText(exception.get_message().c_str());
    }
}

void AdminGUI::handle_remove() {
    try{
        string title;
        string genre;
        string trailer;
        int likes;
        int year;
        this->fetch_data(title, genre, year, likes, trailer);
        this->controller.remove_movie_admin(title, year);
        this->movies_model->reload();
        this->errorMessageTextField->setText("");
    }catch (const AppException& exception){
        this->errorMessageTextField->setText(exception.get_message().c_str());
    }
}

void AdminGUI::handle_update() {
    try{
        string title;
        string genre;
        string trailer;
        int likes;
        int year;
        this->fetch_data(title, genre, year, likes, trailer);
        this->controller.update_movie_admin(title, genre, year, likes, trailer);
        this->movies_model->reload();
        this->errorMessageTextField->setText("");
    }catch (const AppException& exception){
        this->errorMessageTextField->setText(exception.get_message().c_str());
    }
}

void AdminGUI::handle_movie_click(const QModelIndex &index) {
    Movie tmp = this->getRepoMovies()[index.row()];

    this->titleTextField->setText(tmp.get_title().c_str());
    this->genreTextField->setText(tmp.get_genre().c_str());
    this->likesTextField->setText(to_string(tmp.get_likes()).c_str());
    this->yearTextField->setText(to_string(tmp.get_year()).c_str());
    this->trailerTextField->setText(tmp.get_trailer_link().c_str());

    this->movies->selectRow(index.row());

    this->movies_model->reload();
}

void AdminGUI::handle_logout() {
    emit this->logout_clicked();
}

void AdminGUI::fetch_data(std::string &title, std::string &genre, int& year, int& likes, std::string& trailer) {
    title = this->titleTextField->text().toStdString();
    genre = this->genreTextField->text().toStdString();
    std::string year_string = this->yearTextField->text().toStdString();
    std::string likes_string = this->likesTextField->text().toStdString();
    trailer = this->trailerTextField->text().toStdString();

    if(title.empty()){
        throw AppException("Invalid title");
    }
    if(genre.empty()){
        throw AppException("Invalid genre");
    }
    if(year_string.empty()){
        throw AppException("Invalid year");
    }
    if(likes_string.empty()){
        throw AppException("Invalid likes");
    }
    if(trailer.empty()){
        throw AppException("Invalid trailer");
    }

    year = likes = 0;

    for(auto &c:year_string){
        if(c < '0' || c > '9'){
            throw AppException("Invalid number for year");
        }
        year = year * 10 + c - '0';
    }
    for(auto &c:likes_string){
        if(c < '0' || c > '9'){
            throw AppException("Invalid number for like");
        }
        likes = likes * 10 + c - '0';
    }
}

void AdminGUI::show() {
    QWidget::show();
    this->movies_model->reload();
}

void AdminGUI::handle_undo() {
    try{
        this->controller.undo();
    }catch(AppException &exception){
        this->errorMessageTextField->setText(exception.get_message().c_str());
    }
    this->movies_model->reload();
}

void AdminGUI::handle_redo() {
    try{
        this->controller.redo();
    }catch(AppException &exception){
        this->errorMessageTextField->setText(exception.get_message().c_str());
    }
    this->movies_model->reload();
}
