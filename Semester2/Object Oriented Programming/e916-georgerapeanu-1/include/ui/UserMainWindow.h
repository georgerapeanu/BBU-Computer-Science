//
// Created by georgerapeanu on 12.06.2022.
//

#ifndef E916_GEORGERAPEANU_1_USERMAINWINDOW_H
#define E916_GEORGERAPEANU_1_USERMAINWINDOW_H

#include <QWidget>
#include "AbstractObserver.h"
#include "User.h"
#include "Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UserMainWindow; }
QT_END_NAMESPACE

class UserMainWindow : public QWidget, public AbstractObserver {
Q_OBJECT

private:
    void showError(const char* c);

public:
    explicit UserMainWindow(Controller& controller, const User& user, QWidget *parent = nullptr);

    ~UserMainWindow() override;

    virtual void update() override ;

private:
    Ui::UserMainWindow *ui;
    Controller& controller;
    User user;
    int current_question_id;

public slots:
    void clickedAddQuestion();
    void clickedAddAnswer();
    void clickedQuestionCell(int x, int y);
    void counterChanged(int answer_id, int delta);
};


#endif //E916_GEORGERAPEANU_1_USERMAINWINDOW_H
