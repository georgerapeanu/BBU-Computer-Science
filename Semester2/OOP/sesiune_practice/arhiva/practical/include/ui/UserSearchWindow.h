//
// Created by georgerapeanu on 11.06.2022.
//

#ifndef PRACTICAL_USERSEARCHWINDOW_H
#define PRACTICAL_USERSEARCHWINDOW_H

#include <QWidget>
#include "AbstractObserver.h"
#include "Controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class UserSearchWindow; }
QT_END_NAMESPACE

class UserSearchWindow : public QWidget, public AbstractObserver {
Q_OBJECT

public:
    explicit UserSearchWindow(Controller& controller, QWidget *parent = nullptr);

    ~UserSearchWindow() override;

    virtual void update()override;

private:
    Ui::UserSearchWindow *ui;
    Controller& controller;

public slots:
    void textChanged();
};


#endif //PRACTICAL_USERSEARCHWINDOW_H
