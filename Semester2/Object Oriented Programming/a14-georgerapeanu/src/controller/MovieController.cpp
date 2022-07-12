/*!
 * @file MovieController.cpp this file contains the implementations for MovieController
 */

//
// Created by georgerapeanu on 21.03.2022.
//

#pragma once

#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "CSVWatchlist.h"
#include "HTMLWatchlist.h"
#include "MovieController.h"
#include "MemoryRepository.h"
#include "Movie.h"
#include "Exceptions.h"
#include "AddMovieAction.h"
#include "RemoveMovieAction.h"
#include "UpdateMovieAction.h"
#include "AbstractMovieAction.h"

using namespace std;

MovieController::MovieController(AbstractRepository<Movie> &repository, AbstractWatchlist<Movie> &watchlist, UndoActionsStack& undo_stack):watchlist(watchlist), repository(repository), undo_stack(undo_stack) {
}

MovieController::~MovieController() {
    ;
}

void
MovieController::add_movie_admin(const std::string &title, const std::string &genre, const int &year, const int &likes,
                                 const std::string &trailer_link) {
    try{
        this->repository.add(Movie(my_tolower(title), my_tolower(genre), year, likes, trailer_link));
    }catch(const RepositoryException& exception){
        if(exception.get_message() == "Id already exists"){
            throw MovieControllerException("Movie already exists");
        }
    }
    AbstractMovieAction* action = new AddMovieAction(Movie(my_tolower(title), my_tolower(genre), year, likes, trailer_link), this->repository, this->watchlist);
    undo_stack.push_back(action);
}


void MovieController::update_movie_admin(const std::string &title, const std::string &genre, const int &year,
                                         const int &likes, const std::string &trailer_link) {
    Movie tmp;
    try{
        tmp = this->repository.find(Movie(my_tolower(title), "nop", year, 0, "nop"));
    }catch(const RepositoryException& exception){
        ;
    }
    try{
        this->repository.update(Movie(my_tolower(title), my_tolower(genre), year, likes, trailer_link));
    }catch(const RepositoryException& exception){
        if(exception.get_message() == "Id doesn't exist"){
            throw MovieControllerException("Movie doesn't exist");
        }
    }
    try{
        this->watchlist.update(Movie(my_tolower(title), my_tolower(genre), year, likes, trailer_link));
    }catch (const RepositoryException &exception){
        ;
    }
    AbstractMovieAction* action = new UpdateMovieAction(tmp, Movie(my_tolower(title), my_tolower(genre), year, likes, trailer_link), this->repository, this->watchlist);
    undo_stack.push_back(action);
}

void MovieController::remove_movie_admin(const std::string &title, const int &year) {
    Movie tmp;
    try{
        tmp = this->repository.find(Movie(my_tolower(title), "nop", year, 0, "nop"));
    }catch(const RepositoryException& exception){
        ;
    }
    try{
        this->repository.remove(Movie(my_tolower(title), "nop", year, 0, "nop"));
    }catch(const RepositoryException& exception){
        if(exception.get_message() == "Id doesn't exist"){
            throw MovieControllerException("Movie doesn't exist");
        }
    }
    try{
        this->watchlist.remove(Movie(my_tolower(title), "nop", year, 0, "nop"));
    }catch (const RepositoryException &exception){
        ;
    }
    AbstractMovieAction* action = new RemoveMovieAction(tmp, this->repository, this->watchlist);
    undo_stack.push_back(action);
}

Movie MovieController::get_movie_user(const std::string &title, const int &year) {
    try{
        return this->repository.find(Movie(my_tolower(title), "nop", year, 0, "nop"));
    }catch(const RepositoryException& exception){
        if(exception.get_message() == "Id doesn't exist"){
            throw MovieControllerException("Movie doesn't exist");
        }
    }
    return Movie();
}

vector<Movie> MovieController::get_movies_user(const std::string genre) {
    vector<Movie> movies = this->repository.get_all();
    vector<Movie> answer;
    copy_if(movies.begin(), movies.end(), back_inserter(answer), [&](Movie &movie){
        return genre == "" || my_tolower(movie.get_genre()) == my_tolower(genre);
    });
    return answer;
}

void MovieController::add_movie_user(const Movie &movie) {
    try{
        this->watchlist.add(movie);
    }catch(const RepositoryException& exception){
        if(exception.get_message() == "Id already exists"){
            throw MovieControllerException("Movie already in watchlist");
        }
    }
}

void MovieController::remove_movie_user(const Movie &movie) {
    try{
        this->watchlist.remove(movie);
    }catch(const RepositoryException& exception){
        if(exception.get_message() == "Id doesn't exist"){
            throw MovieControllerException("Movie not in watchlist");
        }
    }
}

vector<Movie> MovieController::get_watchlist_user() {
    return this->watchlist.get_all();
}

void MovieController::like_movie_user(const Movie &movie) {
    this->repository.update(Movie(movie.get_title(), movie.get_genre(), movie.get_year(), movie.get_likes() + 1, movie.get_trailer_link()));
}

vector<Movie> MovieController::get_all_movies_admin() {
    return this->repository.get_all();
}

std::string MovieController::my_tolower(const std::string &s) const {
    std::string ans = "";
    for(auto &it:s){
        if('A' <= it && it <= 'Z'){
            ans += it + ('a' - 'A');
        }else{
            ans += it;
        }
    }
    return ans;
}

MovieController &MovieController::operator=(const MovieController &other) {
    this->repository = other.repository;
    this->watchlist = other.watchlist;
    return *this;
}

void MovieController::display_watchlist() const {
    this->watchlist.display();
}

std::vector<Movie> MovieController::get_movies_matching_genre(std::string genre) {
    vector<Movie> movies = this->repository.get_all();
    vector<Movie> answer;
    copy_if(movies.begin(), movies.end(), back_inserter(answer), [&](Movie &movie){
        return genre == "" || movie.get_genre().find(genre) != std::string::npos;
    });
    return answer;
}

void MovieController::undo() {
    this->undo_stack.undo();
}

void MovieController::redo() {
    this->undo_stack.redo();
}