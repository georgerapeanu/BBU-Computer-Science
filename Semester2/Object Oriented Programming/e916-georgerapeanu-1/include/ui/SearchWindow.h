//
// Created by georgerapeanu on 12.06.2022.
//

#ifndef E916_GEORGERAPEANU_1_SEARCHWINDOW_H
#define E916_GEORGERAPEANU_1_SEARCHWINDOW_H

#include <QWidget>
#include "AbstractObserver.h"
#include "Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SearchWindow; }
QT_END_NAMESPACE

class SearchWindow : public QWidget, public AbstractObserver {
Q_OBJECT

public:
    explicit SearchWindow(Controller& controller, QWidget *parent = nullptr);

    ~SearchWindow() override;

    virtual void update() override ;

private:
    Ui::SearchWindow *ui;
    Controller& controller;

public slots:
    void searchTextChanged();
};


#endif //E916_GEORGERAPEANU_1_SEARCHWINDOW_H
