/*!
 * @file MovieValidator.h this file contains the model for the movie validator
 */

//
// Created by georgerapeanu on 18.04.2022.
//

#ifndef A8_9_GEORGERAPEANU_MOVIEVALIDATOR_H
#define A8_9_GEORGERAPEANU_MOVIEVALIDATOR_H
#include "Movie.h"
#include "Exceptions.h"
//! the movie validator
class MovieValidator{
public:
    /*!
     * @brief static method that checks if a given movie is valid
     * @param movie the movie
     * @throws DomainException if movie invalid
     */
    static void validate_movie(const Movie &movie);
};
#endif //A8_9_GEORGERAPEANU_MOVIEVALIDATOR_H
