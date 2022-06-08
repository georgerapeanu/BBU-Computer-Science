//
// Created by georgerapeanu on 08.06.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ProgrammerWindow.h" resolved

#include "ProgrammerWindow.h"
#include "ui_ProgrammerWindow.h"
#include "Exceptions.h"


ProgrammerWindow::ProgrammerWindow(User& user, IssuesModel &model, QWidget *parent) :
        user(user), issues_model(model), QWidget(parent), ui(new Ui::ProgrammerWindow) {
    ui->setupUi(this);
    ui->tableView->setModel(&model);
    this->setWindowTitle(QString::fromStdString(user.getName() + ": " + user.getType()));
    this->activeRow = -1;
}

ProgrammerWindow::~ProgrammerWindow() {
    delete ui;
}

void ProgrammerWindow::deleteActive() {
    try{
        this->issues_model.remove(this->user, this->ui->lineEdit->text().toStdString());
        this->activeRow = -1;
        this->ui->tableView->clearSelection();
    }catch(const AppException &exception){
        this->showError(exception.what());
    }
}

void ProgrammerWindow::resolveActive() {
    try{
        this->issues_model.resolve(this->user, this->ui->lineEdit->text().toStdString());
        this->activeRow = -1;
        this->ui->tableView->clearSelection();
    }catch(const AppException &exception){
        this->showError(exception.what());
    }
}

void ProgrammerWindow::showError(const char *error) {
    QMessageBox* msgBox = new QMessageBox();
    msgBox->setText(error);
    msgBox->show();
}

void ProgrammerWindow::clickedRow(QModelIndex index) {
    this->activeRow = index.row();
    this->ui->tableView->selectRow(this->activeRow);
    this->ui->lineEdit->setText(this->issues_model.data(this->issues_model.index(this->activeRow, 0)).toString());
}

