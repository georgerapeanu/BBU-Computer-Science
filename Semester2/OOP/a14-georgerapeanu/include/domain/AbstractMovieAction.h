//
// Created by georgerapeanu on 23.05.2022.
//

#ifndef A14_GEORGERAPEANU_ABSTRACTMOVIEACTION_H
#define A14_GEORGERAPEANU_ABSTRACTMOVIEACTION_H

#include "Movie.h"
#include "AbstractRepository.h"
#include "AbstractWatchlist.h"

class AbstractMovieAction{
protected:
    Movie movie;
    AbstractRepository<Movie>& movie_repository;
    AbstractWatchlist<Movie>& movie_watchlist;
public:
    AbstractMovieAction(const Movie &movie, AbstractRepository<Movie>& movie_repository, AbstractWatchlist<Movie>&movie_watchlist);
    virtual ~AbstractMovieAction();
    virtual void undo() = 0;
    virtual void redo() = 0;

};

#endif //A14_GEORGERAPEANU_ABSTRACTMOVIEACTION_H
