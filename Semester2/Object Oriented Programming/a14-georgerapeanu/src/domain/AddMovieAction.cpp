//
// Created by georgerapeanu on 23.05.2022.
//

#include "AddMovieAction.h"
#include "Exceptions.h"

AddMovieAction::AddMovieAction(const Movie &movie, AbstractRepository<Movie> &movie_repository,
                               AbstractWatchlist<Movie> &movie_watchlist) : AbstractMovieAction(movie, movie_repository,
                                                                                                movie_watchlist) {

}

void AddMovieAction::undo() {
    try{
        this->movie_watchlist.remove(this->movie);
    }catch (RepositoryException &ex){
        ;
    }
    this->movie_repository.remove(this->movie);
}

void AddMovieAction::redo() {
    this->movie_repository.add(this->movie);
}
