/********************************************************************************
** Form generated from reading UI file 'SearchWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHWINDOW_H
#define UI_SEARCHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchWindow
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *best_question_list;
    QFormLayout *formLayout;
    QLabel *seach_label;
    QLineEdit *search_lineedit;

    void setupUi(QWidget *SearchWindow)
    {
        if (SearchWindow->objectName().isEmpty())
            SearchWindow->setObjectName(QString::fromUtf8("SearchWindow"));
        SearchWindow->resize(577, 476);
        verticalLayout = new QVBoxLayout(SearchWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        best_question_list = new QListWidget(SearchWindow);
        best_question_list->setObjectName(QString::fromUtf8("best_question_list"));

        verticalLayout->addWidget(best_question_list);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        seach_label = new QLabel(SearchWindow);
        seach_label->setObjectName(QString::fromUtf8("seach_label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, seach_label);

        search_lineedit = new QLineEdit(SearchWindow);
        search_lineedit->setObjectName(QString::fromUtf8("search_lineedit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, search_lineedit);


        verticalLayout->addLayout(formLayout);


        retranslateUi(SearchWindow);
        QObject::connect(search_lineedit, SIGNAL(textChanged(QString)), SearchWindow, SLOT(searchTextChanged()));

        QMetaObject::connectSlotsByName(SearchWindow);
    } // setupUi

    void retranslateUi(QWidget *SearchWindow)
    {
        SearchWindow->setWindowTitle(QApplication::translate("SearchWindow", "SearchWindow", nullptr));
        seach_label->setText(QApplication::translate("SearchWindow", "Search:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchWindow: public Ui_SearchWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHWINDOW_H
