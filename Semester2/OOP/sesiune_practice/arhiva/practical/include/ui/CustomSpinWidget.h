//
// Created by georgerapeanu on 11.06.2022.
//

#ifndef PRACTICAL_CUSTOMSPINWIDGET_H
#define PRACTICAL_CUSTOMSPINWIDGET_H

#include <QSpinBox>

class CustomSpinWidget : public QSpinBox{
    Q_OBJECT
    int answer_id;
public:
    CustomSpinWidget(const int answer_id, const int value, QWidget* parent = Q_NULLPTR);

    virtual void stepBy(int step)override;

public:
    signals:
    void change(int answer_id, int delta);
};

#endif //PRACTICAL_CUSTOMSPINWIDGET_H
