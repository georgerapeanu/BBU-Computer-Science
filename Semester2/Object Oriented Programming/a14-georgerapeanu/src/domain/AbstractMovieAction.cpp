//
// Created by georgerapeanu on 23.05.2022.
//

#include "AbstractMovieAction.h"

AbstractMovieAction::AbstractMovieAction(const Movie &movie, AbstractRepository<Movie> &movie_repository,
                                         AbstractWatchlist<Movie> &movie_watchlist): movie(movie), movie_repository(movie_repository), movie_watchlist(movie_watchlist) {

}

AbstractMovieAction::~AbstractMovieAction() {

}
