//
// Created by georgerapeanu on 12.06.2022.
//

#ifndef E916_GEORGERAPEANU_1_MYSPINBOX_H
#define E916_GEORGERAPEANU_1_MYSPINBOX_H

#include <QtWidgets>

class MySpinBox : public QSpinBox{
    Q_OBJECT
    int answer_id;
public:

    MySpinBox(const int answer_id, QWidget* parent = Q_NULLPTR);

    virtual ~MySpinBox();

    virtual void stepBy(int steps)override;

signals:

    void counter_changed(int question_id, int delta);
};


#endif //E916_GEORGERAPEANU_1_MYSPINBOX_H
