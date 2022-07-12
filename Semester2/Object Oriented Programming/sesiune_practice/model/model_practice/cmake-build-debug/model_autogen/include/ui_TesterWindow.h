/********************************************************************************
** Form generated from reading UI file 'TesterWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTERWINDOW_H
#define UI_TESTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TesterWindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QFormLayout *formLayout;
    QLineEdit *lineEdit;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *TesterWindow)
    {
        if (TesterWindow->objectName().isEmpty())
            TesterWindow->setObjectName(QString::fromUtf8("TesterWindow"));
        TesterWindow->resize(400, 291);
        TesterWindow->setMinimumSize(QSize(0, 291));
        verticalLayout_2 = new QVBoxLayout(TesterWindow);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableView(TesterWindow);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        lineEdit = new QLineEdit(TesterWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        label = new QLabel(TesterWindow);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);


        verticalLayout->addLayout(formLayout);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(TesterWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(TesterWindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(lineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(TesterWindow);
        QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), TesterWindow, SLOT(clickedRow(QModelIndex)));
        QObject::connect(pushButton, SIGNAL(clicked()), TesterWindow, SLOT(clickedAdd()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), TesterWindow, SLOT(clickedRemove()));

        QMetaObject::connectSlotsByName(TesterWindow);
    } // setupUi

    void retranslateUi(QWidget *TesterWindow)
    {
        TesterWindow->setWindowTitle(QApplication::translate("TesterWindow", "TesterWindow", nullptr));
        label->setText(QApplication::translate("TesterWindow", "Description:", nullptr));
        pushButton->setText(QApplication::translate("TesterWindow", "Add", nullptr));
        pushButton_2->setText(QApplication::translate("TesterWindow", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TesterWindow: public Ui_TesterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTERWINDOW_H
