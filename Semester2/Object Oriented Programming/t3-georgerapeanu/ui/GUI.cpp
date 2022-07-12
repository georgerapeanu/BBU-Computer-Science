//
// Created by georgerapeanu on 26.05.2022.
//

#include "GUI.h"

GUI::GUI(Controller &controller, QWidget *parrent) : controller(controller),QWidget(parrent){
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->list_label = new QLabel("Document list");
    this->list = new QListWidget();
    mainLayout->addWidget(this->list_label);
    mainLayout->addWidget(this->list);
    this->searchBar = new QLineEdit();
    QFormLayout* formLayout = new QFormLayout();
    mainLayout->addLayout(formLayout);
    formLayout->addRow(tr("Search:"), this->searchBar);
    this->similarity = new QLineEdit();
    this->similarity->setReadOnly(true);
    formLayout->addRow(tr("Similarity"), this->similarity);
    this->show_documents();

    this->similarity->setText("No document selected");

    QObject::connect(this->searchBar, &QLineEdit::textChanged, this, &GUI::show_documents);
    QObject::connect(this->list, &QListWidget::currentRowChanged, this, &GUI::handle_item_change);
}

void GUI::show_documents() {
    std::string topic = this->searchBar->text().toStdString();
    std::vector<Document> tmp = controller.get_all_documents_sorted_by_description_length_containing(topic);
    this->list->clear();
    for(auto it:tmp){
        this->list->addItem(QString::fromStdString(it.to_string()));
    }
}

void GUI::handle_item_change(int row) {
    if(row == -1){
        this->similarity->setText("No document selected");
    }else{
        std::string topic = this->searchBar->text().toStdString();
        std::vector<Document> tmp = controller.get_all_documents_sorted_by_description_length_containing(topic);
        double score = this->controller.get_similarity(tmp[row], topic);
        this->similarity->setText(QString::fromStdString(std::to_string(score)));
    }
}
