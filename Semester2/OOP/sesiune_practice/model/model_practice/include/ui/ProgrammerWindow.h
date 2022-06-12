//
// Created by georgerapeanu on 08.06.2022.
//

#ifndef MODEL_PROGRAMMERWINDOW_H
#define MODEL_PROGRAMMERWINDOW_H

#include <QWidget>
#include "IssueController.h"
#include "IssuesModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ProgrammerWindow; }
QT_END_NAMESPACE

class ProgrammerWindow : public QWidget {
Q_OBJECT

public:
    ProgrammerWindow(User& user, IssuesModel& issues_model, QWidget *parent = nullptr);

    ~ProgrammerWindow() override;

public slots:
    void deleteActive();
    void resolveActive();
    void clickedRow(QModelIndex index);

private:

    User user;
    IssuesModel& issues_model;
    Ui::ProgrammerWindow *ui;
    int activeRow;

    void showError(const char* error);
};


#endif //MODEL_PROGRAMMERWINDOW_H
