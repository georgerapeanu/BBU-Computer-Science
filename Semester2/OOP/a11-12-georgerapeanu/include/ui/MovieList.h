/*!
 * @file MovieList.h this file contains the model for a class that manages movie lists
 */

//
// Created by georgerapeanu on 08.05.2022.
//

#ifndef A11_12_GEORGERAPEANU_MOVIELIST_H
#define A11_12_GEORGERAPEANU_MOVIELIST_H

#include <QtWidgets>
#include "MovieController.h"
#include "Movie.h"
#include <vector>

//! The model of the MovieList structure
class MovieList: public QTableWidget {
Q_OBJECT
private:
    //! This is used in order to be able to get movies from different sources
    std::function<std::vector<Movie>()> getMoviesFunction;
public:
    MovieList(std::function<std::vector<Movie>()> getMoviesFunction, QWidget* parent = Q_NULLPTR);

    void setMoviesFunction(std::function<std::vector<Movie>()> getMoviesFunction);

public slots:
    void reload();
};


#endif //A11_12_GEORGERAPEANU_MOVIELIST_H
