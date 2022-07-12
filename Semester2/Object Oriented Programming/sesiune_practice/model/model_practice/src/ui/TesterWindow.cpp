//
// Created by georgerapeanu on 08.06.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TesterWindow.h" resolved

#include "TesterWindow.h"
#include "ui_TesterWindow.h"
#include "Exceptions.h"


TesterWindow::TesterWindow(User& user, IssuesModel &model, QWidget *parent) :
        QWidget(parent), user(user), model(model),ui(new Ui::TesterWindow) {
    ui->setupUi(this);
    ui->tableView->setModel(&model);
    activeRow = -1;
}

TesterWindow::~TesterWindow() {
    delete ui;
}

void TesterWindow::clickedRow(QModelIndex index) {
    this->activeRow = index.row();
    this->ui->tableView->selectRow(this->activeRow);
    this->ui->lineEdit->setText(this->model.data(this->model.index(this->activeRow, 0)).toString());
}

void TesterWindow::clickedRemove() {
    try{
        this->model.remove(this->user, this->ui->lineEdit->text().toStdString());
        this->activeRow = -1;
        this->ui->tableView->clearSelection();
    }catch(const AppException &exception){
        this->showError(exception.what());
    }
}

void TesterWindow::showError(const char *error) {
    QMessageBox* msgBox = new QMessageBox();
    msgBox->setText(error);
    msgBox->show();
}

void TesterWindow::clickedAdd() {
    try{
        this->model.add(this->user, this->ui->lineEdit->text().toStdString());
        this->activeRow = -1;
        this->ui->tableView->clearSelection();
    }catch(const AppException &exception){
        this->showError(exception.what());
    }
}
