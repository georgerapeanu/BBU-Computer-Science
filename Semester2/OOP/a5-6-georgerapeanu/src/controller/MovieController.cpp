/*!
 * @file MovieController.cpp this file contains the implementations for MovieController
 */

//
// Created by georgerapeanu on 21.03.2022.
//

#pragma once
#include "MovieController.h"
#include "Repository.h"
#include "Movie.h"
#include "Exceptions.h"

MovieController::MovieController() {
    this->watchlist = Repository<Movie>();
    this->repository = Repository<Movie>();
}

MovieController::MovieController(const MovieController &controller) {
    this->watchlist = controller.watchlist;
    this->repository = controller.repository;
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
}


void MovieController::update_movie_admin(const std::string &title, const std::string &genre, const int &year,
                                         const int &likes, const std::string &trailer_link) {
    try{
        this->repository.update(Movie(my_tolower(title), my_tolower(genre), year, likes, trailer_link));
    }catch(const RepositoryException& exception){
        if(exception.get_message() == "Id doesn't exist"){
            throw MovieControllerException("Movie doesn't exist");
        }
    }
}

void MovieController::remove_movie_admin(const std::string &title, const int &year) {
    try{
        this->repository.remove(Movie(my_tolower(title), "", year, 0, ""));
    }catch(const RepositoryException& exception){
        if(exception.get_message() == "Id doesn't exist"){
            throw MovieControllerException("Movie doesn't exist");
        }
    }
}

Movie MovieController::get_movie_user(const std::string &title, const int &year) {
    try{
        return this->repository.find(Movie(my_tolower(title), "", year, 0, ""));
    }catch(const RepositoryException& exception){
        if(exception.get_message() == "Id doesn't exist"){
            throw MovieControllerException("Movie doesn't exist");
        }
    }
    return Movie();
}

DynamicVector<Movie> MovieController::get_movies_user(const std::string genre) {
    DynamicVector<Movie> movies = this->repository.get_all();
    DynamicVector<Movie> answer;
    for(unsigned int i = 0;i < movies.size();i++){
        if(genre == "" || my_tolower(movies[i].get_genre()) == my_tolower(genre)){
            answer.push_back(movies[i]);
        }
    }
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

DynamicVector<Movie> MovieController::get_watchlist_user() {
    return this->watchlist.get_all();
}

void MovieController::like_movie_user(const Movie &movie) {
    this->repository.update(Movie(movie.get_title(), movie.get_genre(), movie.get_year(), movie.get_likes() + 1, movie.get_trailer_link()));
}

DynamicVector<Movie> MovieController::get_all_movies_admin() {
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
