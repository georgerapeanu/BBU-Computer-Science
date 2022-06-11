//
// Created by georgerapeanu on 11.06.2022.
//

#include "CustomSpinWidget.h"
#include <QtWidgets>

CustomSpinWidget::CustomSpinWidget(const int answer_id, const int value, QWidget *parent) : QSpinBox(parent), answer_id(answer_id){
    this->setValue(value);
    this->lineEdit()->setReadOnly(true);
}

#include <iostream>
void CustomSpinWidget::stepBy(int step) {
    std::cerr << "called\n";
    std::cerr << step << std::endl;
    if(step > 0){
        emit this->change(answer_id, 1);
    }else if(step < 0){
        emit this->change(answer_id, -1);
    }
    QAbstractSpinBox::stepBy(step);
}
