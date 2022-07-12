//
// Created by georgerapeanu on 08.06.2022.
//

#ifndef MODEL_ISSUESMODEL_H
#define MODEL_ISSUESMODEL_H

#include <QtWidgets>
#include "IssueController.h"
#include "User.h"

class IssuesModel: public QAbstractTableModel{
    Q_OBJECT

    IssueController& controller;
public:

    IssuesModel(IssueController& controller, QObject* parent = Q_NULLPTR);
    virtual int columnCount(const QModelIndex &parent = QModelIndex())const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex())const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const;

    void resolve(const User& user, const std::string& description);
    void remove(const User& user, const std::string& description);
    void add(const User& user, const std::string& description);
};

#endif //MODEL_ISSUESMODEL_H
