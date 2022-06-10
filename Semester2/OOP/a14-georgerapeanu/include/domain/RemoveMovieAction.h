//
// Created by georgerapeanu on 23.05.2022.
//

#ifndef A14_GEORGERAPEANU_REMOVEMOVIEACTION_H
#define A14_GEORGERAPEANU_REMOVEMOVIEACTION_H

#include "AbstractMovieAction.h"

class RemoveMovieAction : public AbstractMovieAction{
public:
    RemoveMovieAction(const Movie &movie, AbstractRepository<Movie>& movie_repository, AbstractWatchlist<Movie>&movie_watchlist);
    virtual void undo()override;
    virtual void redo()override;
};


#endif //A14_GEORGERAPEANU_REMOVEMOVIEACTION_H
