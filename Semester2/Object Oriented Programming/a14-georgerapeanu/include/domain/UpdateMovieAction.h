//
// Created by georgerapeanu on 23.05.2022.
//

#ifndef A14_GEORGERAPEANU_UPDATEMOVIEACTION_H
#define A14_GEORGERAPEANU_UPDATEMOVIEACTION_H

#include "AbstractMovieAction.h"

class UpdateMovieAction : public AbstractMovieAction{
protected:
    Movie new_movie;
public:
    UpdateMovieAction(const Movie &movie, const Movie &new_movie, AbstractRepository<Movie>& movie_repository, AbstractWatchlist<Movie>&movie_watchlist);
    virtual void undo()override;
    void redo()override;
};


#endif //A14_GEORGERAPEANU_UPDATEMOVIEACTION_H
