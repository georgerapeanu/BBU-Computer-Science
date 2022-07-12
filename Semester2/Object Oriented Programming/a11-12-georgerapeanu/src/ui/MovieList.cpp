/*!
 * @file MovieList.cpp this file contains the imlementation of the struct defined in MovieList.h
 */

//
// Created by georgerapeanu on 08.05.2022.
//

#include "MovieList.h"
#include <vector>
#include <string>

using namespace std;

MovieList::MovieList(std::function<std::vector<Movie>()> getMoviesFunction, QWidget *parent) : QTableWidget(parent){
    this->getMoviesFunction = getMoviesFunction;
    this->setColumnCount(5);
    this->setHorizontalHeaderLabels({"Title", "Genre", "Likes", "Year", "Trailer"});
    this->reload();
}

void MovieList::reload() {
    this->clearContents();
    vector<Movie> movies = getMoviesFunction();
    this->setRowCount(movies.size());
    for(int i = 0;i < (int)movies.size();i++){
        this->setItem(i, 0, new QTableWidgetItem(tr(movies[i].get_title().c_str())));
        this->setItem(i, 1, new QTableWidgetItem(tr(movies[i].get_genre().c_str())));
        this->setItem(i, 2, new QTableWidgetItem(tr(to_string(movies[i].get_likes()).c_str())));
        this->setItem(i, 3, new QTableWidgetItem(tr(to_string(movies[i].get_year()).c_str())));
        this->setItem(i, 4, new QTableWidgetItem(tr(movies[i].get_trailer_link().c_str())));
    }
}

void MovieList::setMoviesFunction(std::function<std::vector<Movie>()> getMoviesFunction) {
    this->getMoviesFunction = getMoviesFunction;
}
