//
// Created by georgerapeanu on 23.05.2022.
//

#include "UpdateMovieAction.h"
#include "Exceptions.h"

UpdateMovieAction::UpdateMovieAction(const Movie &movie, const Movie &new_movie,AbstractRepository<Movie> &movie_repository,
                                     AbstractWatchlist<Movie> &movie_watchlist) : AbstractMovieAction(movie,
                                                                                                      movie_repository,
                                                                                                      movie_watchlist),
                                                                                                      new_movie(new_movie){

}

void UpdateMovieAction::undo() {
    this->movie_repository.update(this->movie);
    try{
        this->movie_watchlist.update(this->movie);
    }catch (RepositoryException &ex){
        ;
    }
}

void UpdateMovieAction::redo() {
    this->movie_repository.update(this->new_movie);
    try{
        this->movie_watchlist.update(this->new_movie);
    }catch (RepositoryException &ex){
        ;
    }
}
