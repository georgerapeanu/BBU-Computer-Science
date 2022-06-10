/********************************************************************************
** Form generated from reading UI file 'ParticipantWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTICIPANTWINDOW_H
#define UI_PARTICIPANTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParticipantWindow
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_2;

    void setupUi(QWidget *ParticipantWindow)
    {
        if (ParticipantWindow->objectName().isEmpty())
            ParticipantWindow->setObjectName(QString::fromUtf8("ParticipantWindow"));
        ParticipantWindow->resize(400, 318);
        verticalLayout = new QVBoxLayout(ParticipantWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(ParticipantWindow);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_2 = new QLabel(ParticipantWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit = new QLineEdit(ParticipantWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit);

        label_3 = new QLabel(ParticipantWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        lineEdit_3 = new QLineEdit(ParticipantWindow);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_3);


        verticalLayout->addLayout(formLayout);

        pushButton = new QPushButton(ParticipantWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label = new QLabel(ParticipantWindow);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit_2 = new QLineEdit(ParticipantWindow);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setReadOnly(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEdit_2);


        verticalLayout->addLayout(formLayout_2);


        retranslateUi(ParticipantWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), ParticipantWindow, SLOT(answer()));
        QObject::connect(lineEdit_3, SIGNAL(textChanged(QString)), ParticipantWindow, SLOT(idChanged()));
        QObject::connect(tableWidget, SIGNAL(cellClicked(int,int)), ParticipantWindow, SLOT(clicked(int,int)));

        QMetaObject::connectSlotsByName(ParticipantWindow);
    } // setupUi

    void retranslateUi(QWidget *ParticipantWindow)
    {
        ParticipantWindow->setWindowTitle(QApplication::translate("ParticipantWindow", "ParticipantWindow", nullptr));
        label_2->setText(QApplication::translate("ParticipantWindow", "Answer:", nullptr));
        label_3->setText(QApplication::translate("ParticipantWindow", "Id:", nullptr));
        pushButton->setText(QApplication::translate("ParticipantWindow", "Answer", nullptr));
        label->setText(QApplication::translate("ParticipantWindow", "Score:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParticipantWindow: public Ui_ParticipantWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTICIPANTWINDOW_H
