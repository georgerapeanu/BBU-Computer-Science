//
// Created by georgerapeanu on 12.06.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UserMainWindow.h" resolved

#include "UserMainWindow.h"
#include "ui_UserMainWindow.h"
#include "AppException.h"
#include "MySpinBox.h"
#include <QMessageBox>

UserMainWindow::UserMainWindow(Controller& controller, const User& user, QWidget *parent) :
        QWidget(parent), ui(new Ui::UserMainWindow), user(user), controller(controller) {
    ui->setupUi(this);

    this->setWindowTitle(QString::fromStdString(user.getName()));

    this->ui->questions_table->setColumnCount(3);
    this->ui->questions_table->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Id")));
    this->ui->questions_table->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Question")));
    this->ui->questions_table->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("By")));

    this->ui->answers_table->setColumnCount(5);
    this->ui->answers_table->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Id")));
    this->ui->answers_table->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Question id")));
    this->ui->answers_table->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("By")));
    this->ui->answers_table->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Answer")));
    this->ui->answers_table->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("Votes")));

    current_question_id = -1;

    this->update();
}

UserMainWindow::~UserMainWindow() {
    delete ui;
}

void UserMainWindow::update() {
    std::vector<Question> questions = this->controller.getAllQuestionsSortedDecreasinglyByAnswerCount();

    this->ui->questions_table->setRowCount((int)questions.size());
    this->ui->questions_table->clearSelection();
    this->ui->answers_table->clearContents();

    for(int i = 0;i < (int)questions.size();i++) {
        this->ui->questions_table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(questions[i].getId()))));
        this->ui->questions_table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString((questions[i].getText()))));
        this->ui->questions_table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString((questions[i].getUserName()))));
        if(current_question_id == questions[i].getId()){
            this->ui->questions_table->selectRow(i);
            std::vector<Answer> answers = this->controller.getAnswersForQuestionSortedDecreasinglyByVotes(current_question_id);
            this->ui->answers_table->setRowCount((int)answers.size());
            for(int i = 0;i < (int)answers.size();i++){
                this->ui->answers_table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(answers[i].getId()))));
                this->ui->answers_table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(answers[i].getQuestionId()))));
                this->ui->answers_table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(answers[i].getAnsweringName())));
                this->ui->answers_table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(answers[i].getText())));
                this->ui->answers_table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString("")));

                MySpinBox* current_spinbox = new MySpinBox(answers[i].getId());
                current_spinbox->setRange(-1000, 1000);
                current_spinbox->setValue(answers[i].getNumberOfVotes());

                connect(current_spinbox, &MySpinBox::counter_changed, this, &UserMainWindow::counterChanged);

                this->ui->answers_table->setCellWidget(i, 4, current_spinbox);

                if(answers[i].getAnsweringName() == user.getName()){
                    current_spinbox->setReadOnly(true);
                    for(int j = 0;j < 5;j++){
                        this->ui->answers_table->item(i, j)->setBackgroundColor(QColor::fromRgb(255, 255, 0));
                    }
                }
            }
        }
    }
}

void UserMainWindow::clickedAddQuestion() {
    try{
        this->controller.addQuestion(user, this->ui->questions_text_lineedit->text().toStdString());
    } catch (const AppException& ex){
        this->showError(ex.what());
    }
}

void UserMainWindow::clickedAddAnswer() {
    try{
        this->controller.addAnswer(user, this->current_question_id, this->ui->answers_text_lineedit->text().toStdString());
    } catch (const AppException& ex){
        this->showError(ex.what());
    }
}

void UserMainWindow::clickedQuestionCell(int x, int y) {
    this->current_question_id = this->ui->questions_table->item(x, 0)->text().toInt();
    this->update();
}

void UserMainWindow::showError(const char *c) {
    QMessageBox* msg = new QMessageBox();
    msg->setText(c);
    msg->show();
}

void UserMainWindow::counterChanged(int answer_id, int delta) {
    this->controller.voteAnswer(user, answer_id, delta);
}

