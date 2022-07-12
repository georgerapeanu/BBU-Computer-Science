//
// Created by georgerapeanu on 23.05.2022.
//

#include "RemoveMovieAction.h"
#include "Exceptions.h"

RemoveMovieAction::RemoveMovieAction(const Movie &movie, AbstractRepository<Movie> &movie_repository,
                                     AbstractWatchlist<Movie> &movie_watchlist) : AbstractMovieAction(movie,
                                                                                                      movie_repository,
                                                                                                      movie_watchlist) {

}

void RemoveMovieAction::undo() {
    this->movie_repository.add(this->movie);
}

void RemoveMovieAction::redo() {
    try{
        this->movie_watchlist.remove(this->movie);
    }catch (RepositoryException &ex){
        ;
    }
    this->movie_repository.remove(this->movie);
}
