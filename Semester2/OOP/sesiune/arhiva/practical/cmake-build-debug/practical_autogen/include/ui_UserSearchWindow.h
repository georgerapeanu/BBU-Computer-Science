/********************************************************************************
** Form generated from reading UI file 'UserSearchWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERSEARCHWINDOW_H
#define UI_USERSEARCHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserSearchWindow
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QWidget *UserSearchWindow)
    {
        if (UserSearchWindow->objectName().isEmpty())
            UserSearchWindow->setObjectName(QString::fromUtf8("UserSearchWindow"));
        UserSearchWindow->resize(400, 574);
        verticalLayout = new QVBoxLayout(UserSearchWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(UserSearchWindow);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(UserSearchWindow);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(UserSearchWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);


        verticalLayout->addLayout(formLayout);


        retranslateUi(UserSearchWindow);
        QObject::connect(lineEdit, SIGNAL(textChanged(QString)), UserSearchWindow, SLOT(textChanged()));

        QMetaObject::connectSlotsByName(UserSearchWindow);
    } // setupUi

    void retranslateUi(QWidget *UserSearchWindow)
    {
        UserSearchWindow->setWindowTitle(QApplication::translate("UserSearchWindow", "UserSearchWindow", nullptr));
        label->setText(QApplication::translate("UserSearchWindow", "Search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserSearchWindow: public Ui_UserSearchWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERSEARCHWINDOW_H
