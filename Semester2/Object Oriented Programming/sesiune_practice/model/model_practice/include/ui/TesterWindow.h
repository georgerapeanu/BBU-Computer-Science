//
// Created by georgerapeanu on 08.06.2022.
//

#ifndef MODEL_TESTERWINDOW_H
#define MODEL_TESTERWINDOW_H

#include <QWidget>
#include "User.h"
#include "IssuesModel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class TesterWindow; }
QT_END_NAMESPACE

class TesterWindow : public QWidget {
Q_OBJECT

    void showError(const char* error);

public:
    explicit TesterWindow(User &user, IssuesModel &model, QWidget *parent = nullptr);

    ~TesterWindow() override;

public slots:
    void clickedRow(QModelIndex index);
    void clickedRemove();
    void clickedAdd();

private:
    Ui::TesterWindow *ui;
    User user;
    IssuesModel &model;
    int activeRow;
};


#endif //MODEL_TESTERWINDOW_H
