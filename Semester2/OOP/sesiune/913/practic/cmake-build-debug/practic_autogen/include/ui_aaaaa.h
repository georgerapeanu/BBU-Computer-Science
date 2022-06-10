/********************************************************************************
** Form generated from reading UI file 'aaaaa.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AAAAA_H
#define UI_AAAAA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_aaaaa
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *aaaaa)
    {
        if (aaaaa->objectName().isEmpty())
            aaaaa->setObjectName(QString::fromUtf8("aaaaa"));
        aaaaa->resize(400, 300);
        pushButton = new QPushButton(aaaaa);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(160, 130, 89, 25));

        retranslateUi(aaaaa);
        QObject::connect(pushButton, SIGNAL(clicked()), aaaaa, SLOT(clicked()));

        QMetaObject::connectSlotsByName(aaaaa);
    } // setupUi

    void retranslateUi(QWidget *aaaaa)
    {
        aaaaa->setWindowTitle(QApplication::translate("aaaaa", "aaaaa", nullptr));
        pushButton->setText(QApplication::translate("aaaaa", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class aaaaa: public Ui_aaaaa {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AAAAA_H
