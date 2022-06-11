//
// Created by georgerapeanu on 11.06.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UserMainWindow.h" resolved

#include "UserMainWindow.h"
#include "ui_UserMainWindow.h"
#include <QMessageBox>
#include "AppException.h"
#include "CustomSpinWidget.h"


UserMainWindow::UserMainWindow(User &user, Controller &controller, QWidget *parent) :
        QWidget(parent), ui(new Ui::UserMainWindow), controller(controller), user(user) {
    ui->setupUi(this);
    current_question_id = -1;

    this->setWindowTitle(QString::fromStdString(user.getName()));
    this->update();
}

UserMainWindow::~UserMainWindow() {
    delete ui;
}

void UserMainWindow::update() {
    this->ui->tableWidget->clear();
    this->ui->tableWidget_2->clear();

    std::vector<Question> questions = this->controller.getQuestionsSortedDecreasinglyByAnswersCount();

    this->ui->tableWidget->setRowCount(questions.size());
    this->ui->tableWidget->setColumnCount(2);

    this->ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Question"));
    this->ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("By"));

    this->ui->tableWidget->clearSelection();
    for(int i = 0;i < (int)questions.size();i++){
        this->ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(questions[i].getText())));
        this->ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(questions[i].getUserName())));
        if(this->current_question_id == questions[i].getId()){
            this->ui->tableWidget->selectRow(i);
        }
    }

    this->ui->tableWidget_2->setRowCount(0);
    this->ui->tableWidget_2->setColumnCount(3);
    this->ui->tableWidget_2->setHorizontalHeaderItem(0, new QTableWidgetItem("By"));
    this->ui->tableWidget_2->setHorizontalHeaderItem(1, new QTableWidgetItem("Answer"));
    this->ui->tableWidget_2->setHorizontalHeaderItem(2, new QTableWidgetItem("Votes"));

    if(this->current_question_id != -1){
        std::vector<Answer> answers = this->controller.getAnswersForQuestionSortedDecreasinglyByVotes(current_question_id);

        this->ui->tableWidget_2->setRowCount(answers.size());

        for(int i = 0;i < (int)answers.size();i++){
            this->ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(answers[i].getAnsweringUserName())));
            this->ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(answers[i].getAnswerText())));
            this->ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem());
            CustomSpinWidget* tmp = new CustomSpinWidget(answers[i].getId(), answers[i].getVotes());
            connect(tmp, &CustomSpinWidget::change, this, &UserMainWindow::handleVote);
            if(user.getName() == answers[i].getAnsweringUserName()){
                tmp->setDisabled(true);
            }
            this->ui->tableWidget_2->setCellWidget(i, 2, tmp);

            if(answers[i].getAnsweringUserName() == user.getName()){
                this->ui->tableWidget_2->item(i, 0)->setBackgroundColor(QColor::fromRgb(255, 255, 0));
                this->ui->tableWidget_2->item(i, 1)->setBackgroundColor(QColor::fromRgb(255, 255, 0));
                this->ui->tableWidget_2->item(i, 2)->setBackgroundColor(QColor::fromRgb(255, 255, 0));
            }
        }
    }else{
        this->ui->tableWidget_2->setRowCount(0);
    }
}

void UserMainWindow::addQuestion() {
    try{
        this->controller.addQuestion(this->user, this->ui->lineEdit->text().toStdString());
    }catch(AppException &ex){
        this->showError(ex.what());
    }
}

void UserMainWindow::clickedQuestion(int x, int y) {
    this->current_question_id = this->controller.getQuestionsSortedDecreasinglyByAnswersCount()[x].getId();
    this->update();

}

void UserMainWindow::addAnswer() {
    try{
        if(current_question_id == -1){
            throw AppException("No question selected");
        }
        this->controller.addAnswer(this->user, this->current_question_id, this->ui->lineEdit_2->text().toStdString());
    }catch(AppException &ex){
        this->showError(ex.what());
    }
}

void UserMainWindow::showError(const char *string) {
    QMessageBox* tmp = new QMessageBox();
    tmp->setText(string);
    tmp->show();
}

void UserMainWindow::handleVote(int answer_id, int delta) {
    this->controller.voteAnswer(user, answer_id, delta);
}

///STARTED 12:56
///BREAK from 14:39 -> 1:43
///RESTART from 15:34
/// Finished all but votes at 16:11 /// 33
///subtotal 2:16
///14 minutes left for spinbox
///so until 16:25
//kinda finished at 16:40, there is just a bug that it increases twice for some reason
//16:42 fixed
//total time: 2:45