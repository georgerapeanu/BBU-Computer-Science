//
// Created by georgerapeanu on 09.06.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ParticipantWindow.h" resolved

#include <QMessageBox>
#include "ParticipantWindow.h"
#include "ui_ParticipantWindow.h"
#include "AppException.h"


ParticipantWindow::ParticipantWindow(Participant& participant, Controller& controller, QWidget *parent) :
        QWidget(parent), ui(new Ui::ParticipantWindow), controller(controller), participant(participant) {
    ui->setupUi(this);
    this->controller.attachObserver(this);
    this->setWindowTitle(QString::fromStdString(participant.getName()));
    this->update();
}

ParticipantWindow::~ParticipantWindow() {
    delete ui;
}

void ParticipantWindow::update() {
    std::vector<Question> tmp = this->controller.getQuestionsSortedByScoreDescendingly();
    this->ui->tableWidget->clear();
    this->ui->tableWidget->setRowCount((int)tmp.size());
    this->ui->tableWidget->setColumnCount(3);
    this->ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromStdString("Id")));
    this->ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromStdString("Question")));
    this->ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromStdString("Score")));
    int idx = 0;
    for(const auto &it:tmp){
        this->ui->tableWidget->setItem(idx, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(it.getId()))));
        this->ui->tableWidget->setItem(idx, 1, new QTableWidgetItem(QString::fromStdString(it.getText())));
        this->ui->tableWidget->setItem(idx, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(it.getScore()))));
        if(answered.count(std::to_string(it.getId()))){
            for(int i = 0;i < 3;i++){
                this->ui->tableWidget->item(idx, i)->setBackgroundColor(QColor::fromRgb(0, 255, 0));
            }
        }
        idx++;
    }
    this->participant = controller.getUpdatedParticipant(participant);
    this->ui->lineEdit_2->setText(QString::fromStdString(std::to_string(participant.getScore())));
}

void ParticipantWindow::answer() {
    std::string id = "";
    id = this->ui->lineEdit_3->text().toStdString();
    try{
        stoi(id);
    }catch(const std::invalid_argument &ex){
        id = "-1";
    }
    std::string answer = this->ui->lineEdit->text().toStdString();
    if(answered.count(id)){
        this->ui->pushButton->setDisabled(true);
        return ;
    }
    try {
        this->controller.answerQuestion(participant, stoi(id), answer);
        answered.insert(id);
        this->update();
    }catch(const AppException& ex){
        QMessageBox* msgBox = new QMessageBox();
        msgBox->setText(ex.what());
        msgBox->show();
    }
}

void ParticipantWindow::clicked(int x, int y) {
    this->ui->lineEdit_3->setText(QString::fromStdString(std::to_string(this->controller.getQuestionsSortedByScoreDescendingly()[x].getId())));
}

void ParticipantWindow::idChanged() {
    this->ui->pushButton->setDisabled(false);
}



