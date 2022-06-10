/*!
 * @file MovieList.cpp this file contains the imlementation of the struct defined in MovieList.h
 */

//
// Created by georgerapeanu on 08.05.2022.
//

#include "MovieListModel.h"
#include <vector>
#include <string>

using namespace std;

MovieListModel::MovieListModel(std::function<std::vector<Movie>()> getMoviesFunction, QWidget *parent) : QAbstractTableModel(parent){
    this->getMoviesFunction = getMoviesFunction;
}


void MovieListModel::setMoviesFunction(std::function<std::vector<Movie>()> getMoviesFunction) {
    this->getMoviesFunction = getMoviesFunction;
}

int MovieListModel::rowCount(const QModelIndex &parent) const {
    return this->getMoviesFunction().size();
}

int MovieListModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant MovieListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch(section){
            case 0: return tr("Title");
            case 1: return tr("Genre");
            case 2: return tr("Likes");
            case 3: return tr("Year");
            case 4: return tr("Trailer");
        }
    }
    return QVariant();
}

QVariant MovieListModel::data(const QModelIndex &index, int role) const {
    if(role == Qt::DisplayRole){
        switch(index.column()){
            case 0: return QString::fromStdString(this->getMoviesFunction()[index.row()].get_title());
            case 1: return QString::fromStdString(this->getMoviesFunction()[index.row()].get_genre());
            case 2: return QString::fromStdString(std::to_string(this->getMoviesFunction()[index.row()].get_likes()));
            case 3: return QString::fromStdString(std::to_string(this->getMoviesFunction()[index.row()].get_year()));
            case 4: return QString::fromStdString(this->getMoviesFunction()[index.row()].get_trailer_link());
        }
    }
    return QVariant();
}

void MovieListModel::reload() {
    beginResetModel();
    endResetModel();
    emit this->dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}


