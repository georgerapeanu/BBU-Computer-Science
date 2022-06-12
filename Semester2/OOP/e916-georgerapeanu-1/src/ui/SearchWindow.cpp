//
// Created by georgerapeanu on 12.06.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SearchWindow.h" resolved

#include "SearchWindow.h"
#include "ui_SearchWindow.h"


SearchWindow::SearchWindow(Controller& controller, QWidget *parent) :
        QWidget(parent), ui(new Ui::SearchWindow), controller(controller){
    ui->setupUi(this);
    this->update();
}

SearchWindow::~SearchWindow() {
    delete ui;
}

void SearchWindow::update() {
    this->ui->best_question_list->clear();
    Question best_question = this->controller.getBestMatchingQuestion(this->ui->search_lineedit->text().toStdString());
    if(best_question == Question()){
        return ;
    }
    this->ui->best_question_list->addItem(QString::fromStdString(
                "Question " + std::to_string(best_question.getId()) + ":" +
                best_question.getText() + " by " +
                best_question.getUserName()
            ));
    std::vector<Answer> answers = controller.getAnswersForQuestionSortedDecreasinglyByVotes(best_question.getId());
    answers.resize(std::min(3, (int)answers.size()));
    for(const auto& answer:answers){
        this->ui->best_question_list->addItem(QString::fromStdString(
                "\tAnswer " + std::to_string(answer.getId()) + ":" +
                answer.getText() + " by " +
                answer.getAnsweringName() + " with " +
                std::to_string(answer.getNumberOfVotes()) + " votes"
        ));
    }
}

void SearchWindow::searchTextChanged() {
    this->update();
}

