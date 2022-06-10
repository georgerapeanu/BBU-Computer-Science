//
// Created by georgerapeanu on 09.06.2022.
//

#ifndef PRACTIC_PRESENTERWINDOW_H
#define PRACTIC_PRESENTERWINDOW_H

#include <QWidget>
#include "Controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class PresenterWindow; }
QT_END_NAMESPACE

class PresenterWindow : public QWidget, AbstractObserver {
Q_OBJECT

public:
    explicit PresenterWindow(Controller& controller, QWidget *parent = nullptr);

    ~PresenterWindow() override;
    virtual void update()override;

private:
    Ui::PresenterWindow *ui;
    Controller& controller;

public slots:
    void clickedAdd();
};


#endif //PRACTIC_PRESENTERWINDOW_H
