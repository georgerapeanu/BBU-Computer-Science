//
// Created by georgerapeanu on 23.05.2022.
//

#ifndef A14_GEORGERAPEANU_ADDMOVIEACTION_H
#define A14_GEORGERAPEANU_ADDMOVIEACTION_H

#include "AbstractMovieAction.h"

class AddMovieAction : public AbstractMovieAction{
public:
    AddMovieAction(const Movie &movie, AbstractRepository<Movie>& movie_repository, AbstractWatchlist<Movie>&movie_watchlist);
    virtual void undo()override;
    virtual void redo()override;
};

#endif //A14_GEORGERAPEANU_ADDMOVIEACTION_H
