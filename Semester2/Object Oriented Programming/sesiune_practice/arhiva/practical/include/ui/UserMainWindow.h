//
// Created by georgerapeanu on 11.06.2022.
//

#ifndef PRACTICAL_USERMAINWINDOW_H
#define PRACTICAL_USERMAINWINDOW_H

#include <QWidget>
#include "AbstractObserver.h"
#include "Controller.h"
#include "User.h"
#include <QSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui { class UserMainWindow; }
QT_END_NAMESPACE

class UserMainWindow : public QWidget, public AbstractObserver {
Q_OBJECT

public:
    explicit UserMainWindow(User& user,Controller& controller, QWidget *parent = nullptr);

    ~UserMainWindow() override;

private:
    Controller& controller;
    User user;
    Ui::UserMainWindow *ui;
    int current_question_id;
    //std::vector<QSpinBox*>

    virtual void update()override;
    void showError(const char *string);

public slots:
    void addQuestion();
    void addAnswer();
    void clickedQuestion(int x, int y);

    void handleVote(int answer_id, int delta);
};


#endif //PRACTICAL_USERMAINWINDOW_H
