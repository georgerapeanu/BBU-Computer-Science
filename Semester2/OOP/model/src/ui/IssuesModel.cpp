//
// Created by georgerapeanu on 08.06.2022.
//

#include "IssuesModel.h"
#include "Exceptions.h"

IssuesModel::IssuesModel(IssueController &controller, QObject* parent):controller(controller), QAbstractTableModel(parent) {
    ;
}

int IssuesModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

int IssuesModel::rowCount(const QModelIndex &parent) const {
    return this->controller.getAllIssuesSortedByStatusAndDescription().size();
}

QVariant IssuesModel::data(const QModelIndex &index, int role) const {
    if(role == Qt::DisplayRole){
        switch(index.column()){
            case 0: return QString::fromStdString(this->controller.getAllIssuesSortedByStatusAndDescription()[index.row()].getDescription());
            case 1: return QString::fromStdString(this->controller.getAllIssuesSortedByStatusAndDescription()[index.row()].getStatus() == Issue::OPEN ? "open":"closed");
            case 2: return QString::fromStdString(this->controller.getAllIssuesSortedByStatusAndDescription()[index.row()].getReporter());
            case 3: return QString::fromStdString(this->controller.getAllIssuesSortedByStatusAndDescription()[index.row()].getSolver());
        }
    }
    return QVariant();
}

QVariant IssuesModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole && orientation == Qt::Orientation::Horizontal){
        switch(section){
            case 0: return QString("Description");
            case 1: return QString("Status");
            case 2: return QString("Reporter");
            case 3: return QString("Solver");
        }
    }
    return QVariant();
}

void IssuesModel::resolve(const User &user, const std::string& description) {
    this->beginResetModel();
    try{
        this->controller.resolveIssue(description, user);
    }catch(const AppException &ex){
        this->endResetModel();
        throw ex;
    }

    this->endResetModel();
}

void IssuesModel::remove(const User &user, const std::string& description) {
    this->beginResetModel();
    try{
        this->controller.removeIssue(description, user);
    }catch(const AppException &ex){
        this->endResetModel();
        throw ex;
    }

    this->endResetModel();
}

void IssuesModel::add(const User &user, const std::string &description) {
    this->beginResetModel();
    try{
        this->controller.addIssue(description, user);
    }catch(const AppException &ex){
        this->endResetModel();
        throw ex;
    }

    this->endResetModel();
}

