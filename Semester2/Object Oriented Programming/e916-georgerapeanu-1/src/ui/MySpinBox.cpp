//
// Created by georgerapeanu on 12.06.2022.
//

#include "MySpinBox.h"

MySpinBox::MySpinBox(const int answer_id, QWidget *parent) : QSpinBox(parent), answer_id(answer_id){
    this->lineEdit()->setReadOnly(true);
}

void MySpinBox::stepBy(int steps) {
    QSpinBox::stepBy(steps);
    if(steps > 0) {
        emit this->counter_changed(this->answer_id, 1);
    }else if(steps < 0){
        emit this->counter_changed(this->answer_id, -1);
    }
}

MySpinBox::~MySpinBox() {

}
