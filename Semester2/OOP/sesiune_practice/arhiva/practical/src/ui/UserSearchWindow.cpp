//
// Created by georgerapeanu on 11.06.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UserSearchWindow.h" resolved

#include "UserSearchWindow.h"
#include "ui_UserSearchWindow.h"


UserSearchWindow::UserSearchWindow(Controller& controller, QWidget *parent) :
        QWidget(parent), ui(new Ui::UserSearchWindow), controller(controller) {
    ui->setupUi(this);
    this->setWindowTitle("Search");
    this->update();
}

UserSearchWindow::~UserSearchWindow() {
    delete ui;
}

void UserSearchWindow::update() {
    std::string search_text = this->ui->lineEdit->text().toStdString();
    this->ui->listWidget->clear();
    Question best_question = this->controller.getBestMatchingQuestion(search_text);
    if(best_question != Question()){
        this->ui->listWidget->addItem(QString::fromStdString(
                best_question.getText() + " by " + best_question.getUserName()
                ));
        std::vector<Answer> answers = this->controller.getAnswersForQuestionSortedDecreasinglyByVotes(best_question.getId());
        answers.resize(std::min((int)answers.size(), 3));
        for(auto &answer:answers){
            this->ui->listWidget->addItem(QString::fromStdString(
                    std::string("\t") + std::string("Votes: ") + std::to_string(answer.getVotes()) + " " + answer.getAnswerText() + " by " + answer.getAnsweringUserName()
            ));
        }
    }

}

void UserSearchWindow::textChanged() {
    this->update();
}

