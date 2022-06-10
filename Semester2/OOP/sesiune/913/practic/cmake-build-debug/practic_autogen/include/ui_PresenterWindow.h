/********************************************************************************
** Form generated from reading UI file 'PresenterWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRESENTERWINDOW_H
#define UI_PRESENTERWINDOW_H

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

class Ui_PresenterWindow
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QFormLayout *formLayout_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton;

    void setupUi(QWidget *PresenterWindow)
    {
        if (PresenterWindow->objectName().isEmpty())
            PresenterWindow->setObjectName(QString::fromUtf8("PresenterWindow"));
        PresenterWindow->resize(400, 393);
        verticalLayout = new QVBoxLayout(PresenterWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(PresenterWindow);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label_4 = new QLabel(PresenterWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_3->setWidget(5, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(PresenterWindow);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(PresenterWindow);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(PresenterWindow);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_3->setWidget(6, QFormLayout::LabelRole, label_7);

        lineEdit_7 = new QLineEdit(PresenterWindow);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        formLayout_3->setWidget(6, QFormLayout::FieldRole, lineEdit_7);

        lineEdit_6 = new QLineEdit(PresenterWindow);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        formLayout_3->setWidget(5, QFormLayout::FieldRole, lineEdit_6);

        lineEdit_5 = new QLineEdit(PresenterWindow);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        formLayout_3->setWidget(3, QFormLayout::FieldRole, lineEdit_5);

        lineEdit_4 = new QLineEdit(PresenterWindow);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, lineEdit_4);


        verticalLayout->addLayout(formLayout_3);

        pushButton = new QPushButton(PresenterWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(PresenterWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), PresenterWindow, SLOT(clickedAdd()));

        QMetaObject::connectSlotsByName(PresenterWindow);
    } // setupUi

    void retranslateUi(QWidget *PresenterWindow)
    {
        PresenterWindow->setWindowTitle(QApplication::translate("PresenterWindow", "PresenterWindow", nullptr));
        label_4->setText(QApplication::translate("PresenterWindow", "Answer:", nullptr));
        label_5->setText(QApplication::translate("PresenterWindow", "Id:", nullptr));
        label_6->setText(QApplication::translate("PresenterWindow", "Text", nullptr));
        label_7->setText(QApplication::translate("PresenterWindow", "Score", nullptr));
        pushButton->setText(QApplication::translate("PresenterWindow", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PresenterWindow: public Ui_PresenterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRESENTERWINDOW_H
