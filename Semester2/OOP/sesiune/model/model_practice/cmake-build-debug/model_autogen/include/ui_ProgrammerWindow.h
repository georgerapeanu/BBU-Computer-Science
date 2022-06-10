/********************************************************************************
** Form generated from reading UI file 'ProgrammerWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRAMMERWINDOW_H
#define UI_PROGRAMMERWINDOW_H

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

class Ui_ProgrammerWindow
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

    void setupUi(QWidget *ProgrammerWindow)
    {
        if (ProgrammerWindow->objectName().isEmpty())
            ProgrammerWindow->setObjectName(QString::fromUtf8("ProgrammerWindow"));
        ProgrammerWindow->resize(400, 284);
        ProgrammerWindow->setMinimumSize(QSize(0, 284));
        verticalLayout_2 = new QVBoxLayout(ProgrammerWindow);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableView(ProgrammerWindow);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        lineEdit = new QLineEdit(ProgrammerWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        label = new QLabel(ProgrammerWindow);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);


        verticalLayout->addLayout(formLayout);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(ProgrammerWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(ProgrammerWindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(lineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(ProgrammerWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), ProgrammerWindow, SLOT(resolveActive()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), ProgrammerWindow, SLOT(deleteActive()));
        QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), ProgrammerWindow, SLOT(clickedRow(QModelIndex)));

        QMetaObject::connectSlotsByName(ProgrammerWindow);
    } // setupUi

    void retranslateUi(QWidget *ProgrammerWindow)
    {
        ProgrammerWindow->setWindowTitle(QApplication::translate("ProgrammerWindow", "ProgrammerWindow", nullptr));
        label->setText(QApplication::translate("ProgrammerWindow", "Description:", nullptr));
        pushButton->setText(QApplication::translate("ProgrammerWindow", "Resolve", nullptr));
        pushButton_2->setText(QApplication::translate("ProgrammerWindow", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProgrammerWindow: public Ui_ProgrammerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRAMMERWINDOW_H
