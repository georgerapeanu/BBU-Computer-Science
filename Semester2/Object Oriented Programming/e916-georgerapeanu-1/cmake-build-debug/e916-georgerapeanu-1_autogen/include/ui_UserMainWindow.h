/********************************************************************************
** Form generated from reading UI file 'UserMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMAINWINDOW_H
#define UI_USERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserMainWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *questions_vertical_layout;
    QLabel *questions_label;
    QTableWidget *questions_table;
    QFormLayout *questions_form_layout;
    QLabel *questions_text_label;
    QLineEdit *questions_text_lineedit;
    QPushButton *questions_add_button;
    QVBoxLayout *answers_vertical_layout;
    QLabel *answers_label;
    QTableWidget *answers_table;
    QFormLayout *answers_form_layout;
    QLabel *answets_text_label;
    QLineEdit *answers_text_lineedit;
    QPushButton *answers_add_button;

    void setupUi(QWidget *UserMainWindow)
    {
        if (UserMainWindow->objectName().isEmpty())
            UserMainWindow->setObjectName(QString::fromUtf8("UserMainWindow"));
        UserMainWindow->resize(781, 527);
        horizontalLayout = new QHBoxLayout(UserMainWindow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        questions_vertical_layout = new QVBoxLayout();
        questions_vertical_layout->setObjectName(QString::fromUtf8("questions_vertical_layout"));
        questions_label = new QLabel(UserMainWindow);
        questions_label->setObjectName(QString::fromUtf8("questions_label"));

        questions_vertical_layout->addWidget(questions_label);

        questions_table = new QTableWidget(UserMainWindow);
        questions_table->setObjectName(QString::fromUtf8("questions_table"));

        questions_vertical_layout->addWidget(questions_table);

        questions_form_layout = new QFormLayout();
        questions_form_layout->setObjectName(QString::fromUtf8("questions_form_layout"));
        questions_text_label = new QLabel(UserMainWindow);
        questions_text_label->setObjectName(QString::fromUtf8("questions_text_label"));

        questions_form_layout->setWidget(0, QFormLayout::LabelRole, questions_text_label);

        questions_text_lineedit = new QLineEdit(UserMainWindow);
        questions_text_lineedit->setObjectName(QString::fromUtf8("questions_text_lineedit"));

        questions_form_layout->setWidget(0, QFormLayout::FieldRole, questions_text_lineedit);


        questions_vertical_layout->addLayout(questions_form_layout);

        questions_add_button = new QPushButton(UserMainWindow);
        questions_add_button->setObjectName(QString::fromUtf8("questions_add_button"));

        questions_vertical_layout->addWidget(questions_add_button);


        horizontalLayout->addLayout(questions_vertical_layout);

        answers_vertical_layout = new QVBoxLayout();
        answers_vertical_layout->setObjectName(QString::fromUtf8("answers_vertical_layout"));
        answers_label = new QLabel(UserMainWindow);
        answers_label->setObjectName(QString::fromUtf8("answers_label"));

        answers_vertical_layout->addWidget(answers_label);

        answers_table = new QTableWidget(UserMainWindow);
        answers_table->setObjectName(QString::fromUtf8("answers_table"));

        answers_vertical_layout->addWidget(answers_table);

        answers_form_layout = new QFormLayout();
        answers_form_layout->setObjectName(QString::fromUtf8("answers_form_layout"));
        answets_text_label = new QLabel(UserMainWindow);
        answets_text_label->setObjectName(QString::fromUtf8("answets_text_label"));

        answers_form_layout->setWidget(0, QFormLayout::LabelRole, answets_text_label);

        answers_text_lineedit = new QLineEdit(UserMainWindow);
        answers_text_lineedit->setObjectName(QString::fromUtf8("answers_text_lineedit"));

        answers_form_layout->setWidget(0, QFormLayout::FieldRole, answers_text_lineedit);


        answers_vertical_layout->addLayout(answers_form_layout);

        answers_add_button = new QPushButton(UserMainWindow);
        answers_add_button->setObjectName(QString::fromUtf8("answers_add_button"));

        answers_vertical_layout->addWidget(answers_add_button);


        horizontalLayout->addLayout(answers_vertical_layout);


        retranslateUi(UserMainWindow);
        QObject::connect(questions_table, SIGNAL(cellClicked(int,int)), UserMainWindow, SLOT(clickedQuestionCell(int,int)));
        QObject::connect(questions_add_button, SIGNAL(clicked()), UserMainWindow, SLOT(clickedAddQuestion()));
        QObject::connect(answers_add_button, SIGNAL(clicked()), UserMainWindow, SLOT(clickedAddAnswer()));

        QMetaObject::connectSlotsByName(UserMainWindow);
    } // setupUi

    void retranslateUi(QWidget *UserMainWindow)
    {
        UserMainWindow->setWindowTitle(QApplication::translate("UserMainWindow", "UserMainWindow", nullptr));
        questions_label->setText(QApplication::translate("UserMainWindow", "Questions:", nullptr));
        questions_text_label->setText(QApplication::translate("UserMainWindow", "Text:", nullptr));
        questions_add_button->setText(QApplication::translate("UserMainWindow", "Add question", nullptr));
        answers_label->setText(QApplication::translate("UserMainWindow", "Answers:", nullptr));
        answets_text_label->setText(QApplication::translate("UserMainWindow", "Text:", nullptr));
        answers_add_button->setText(QApplication::translate("UserMainWindow", "Add answer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserMainWindow: public Ui_UserMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMAINWINDOW_H
