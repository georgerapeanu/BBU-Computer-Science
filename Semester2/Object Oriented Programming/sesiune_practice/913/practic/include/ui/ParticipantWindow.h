//
// Created by georgerapeanu on 09.06.2022.
//

#ifndef PRACTIC_PARTICIPANTWINDOW_H
#define PRACTIC_PARTICIPANTWINDOW_H

#include <QWidget>
#include "AbstractObserver.h"
#include "Controller.h"
#include <set>


QT_BEGIN_NAMESPACE
namespace Ui { class ParticipantWindow; }
QT_END_NAMESPACE

class ParticipantWindow : public QWidget, AbstractObserver {
Q_OBJECT

public:
    explicit ParticipantWindow(Participant& participant, Controller& controller, QWidget *parent = nullptr);

    ~ParticipantWindow() override;
    virtual void update()override;
private:
    Ui::ParticipantWindow *ui;
    Controller& controller;
    Participant participant;
    std::set<std::string> answered;

public slots:
    void answer();
    void clicked(int x, int y);
    void idChanged();
};


#endif //PRACTIC_PARTICIPANTWINDOW_H
