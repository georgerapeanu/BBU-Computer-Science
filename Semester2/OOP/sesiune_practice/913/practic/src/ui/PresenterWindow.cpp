//
// Created by georgerapeanu on 09.06.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PresenterWindow.h" resolved

#include <QMessageBox>
#include "PresenterWindow.h"
#include "ui_PresenterWindow.h"
#include "AppException.h"


PresenterWindow::PresenterWindow(Controller& controller, QWidget *parent) :
        QWidget(parent), ui(new Ui::PresenterWindow), controller(controller) {
    ui->setupUi(this);
    this->update();
    this->setWindowTitle("Presenter");
    this->controller.attachObserver(this);
}

PresenterWindow::~PresenterWindow() {
    delete ui;
}

void PresenterWindow::update() {

    std::vector<Question> tmp = this->controller.getQuestionsSortedById();
    this->ui->tableWidget->clear();
    this->ui->tableWidget->setRowCount((int)tmp.size());
    this->ui->tableWidget->setColumnCount(4);
    this->ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromStdString("Id")));
    this->ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromStdString("Question")));
    this->ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromStdString("Answer")));
    this->ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(QString::fromStdString("Score")));
    int idx = 0;
    for(const auto &it:tmp){
        this->ui->tableWidget->setItem(idx, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(it.getId()))));
        this->ui->tableWidget->setItem(idx, 1, new QTableWidgetItem(QString::fromStdString(it.getText())));
        this->ui->tableWidget->setItem(idx, 2, new QTableWidgetItem(QString::fromStdString(it.getCorrectAnswer())));
        this->ui->tableWidget->setItem(idx, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(it.getScore()))));
        idx++;
    }
}

void PresenterWindow::clickedAdd() {
    std::string id_string = this->ui->lineEdit_4->text().toStdString();
    std::string text_string = this->ui->lineEdit_5->text().toStdString();
    std::string answer_string = this->ui->lineEdit_6->text().toStdString();
    std::string score_string = this->ui->lineEdit_7->text().toStdString();
    int id;
    int score;
    try{
        try{
            id = std::stoi(id_string);
        }catch(std::exception& ex){
            throw AppException("Invalid id");
        }
        try{
            score = std::stoi(score_string);
        }catch(std::exception& ex){
            throw AppException("Invalid score");
        }
        controller.addQuestion(id, text_string, answer_string, score);
    }catch (const AppException& ex){
        QMessageBox* msgBox = new QMessageBox();
        msgBox->setText(ex.what());
        msgBox->show();
    }
}


