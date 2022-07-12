/*!
 * @file MovieValidator.cpp this file contains the implementation for the movie validator
 */

//
// Created by georgerapeanu on 18.04.2022.
//

#pragma once
#include "Movie.h"
#include "MovieValidator.h"
#include "Exceptions.h"

void MovieValidator::validate_movie(const Movie &movie) {
    if(movie.get_likes() < 0){
        throw DomainException("Movie invalid");
    }
    if(movie.get_year() < 0){
        throw DomainException("Movie invalid");
    }
    if(movie.get_trailer_link() == ""){
        throw DomainException("Movie invalid");
    }
    if(movie.get_title() == ""){
        throw DomainException("Movie invalid");
    }
    if(movie.get_genre() == ""){
        throw DomainException("Movie invalid");
    }
}
