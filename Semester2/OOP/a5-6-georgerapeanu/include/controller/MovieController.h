/*!
 * @file MovieController.h this file contains the model for a movie controller
 */

//
// Created by georgerapeanu on 21.03.2022.
//

#ifndef A5_6_GEORGERAPEANU_MOVIECONTROLLER_H
#define A5_6_GEORGERAPEANU_MOVIECONTROLLER_H
#pragma once
#include "Movie.h"
#include "Repository.h"

//! the model of the MovieController class
class MovieController{
    //! the repository which holds all the movies
    Repository<Movie> repository;
    //! the current watchlist of the user
    Repository<Movie> watchlist;
public:

    /*!
     * @brief The default constructor of the movie controller
     */
    MovieController();
    /*!
     * @brief The default copy constructor of the movie controller
     */

    MovieController(const MovieController &controller);
    /*!
     * @brief The destructor of the movie controller
     */
    ~MovieController();


    /*!
     * @brief adds a movie to the movie repository
     * @param title the title of the movie to be added
     * @param genre the genre of the movie to be added
     * @param year the year of the movie to be added
     * @param likes the number of likes of the movie to be added
     * @param trailer_link the trailer of the movie to be added
     */
    void add_movie_admin(const std::string &title, const std::string &genre, const int &year, const int &likes, const std::string &trailer_link);
    /*!
      * @brief updates a movie to the movie repository
     * @param title the title of the movie to be added
     * @param genre the genre of the movie to be added
     * @param year the year of the movie to be added
     * @param likes the number of likes of the movie to be added
     * @param trailer_link the trailer of the movie to be added
     */
    void update_movie_admin(const std::string &title, const std::string &genre, const int &year, const int &likes, const std::string &trailer_link);
    /*!
     * @brief this function removes a movie from the movie repository
     * @param title the title of the movie
     * @param year the year of the movie
     */
    void remove_movie_admin(const std::string &title, const int &year);
    /*!
     * @brief this function finds a movie in the repository
     * @param title the title of the movie
     * @param year the year of the movie
     */
    Movie get_movie_user(const std::string &title, const int &year);

    /*!
     * @brief this function returns all the movies from the repository
     * @return a list of the movies from the repository
     */
    DynamicVector<Movie> get_all_movies_admin();

    /*!
     * @brief this function gets a vector with all the movies that have a given genre. If the genre is empty, all genres are considered.
     * @param genre the genre of the movies
     * @return a vector of the movies
     */
    DynamicVector<Movie> get_movies_user(const std::string genre);

    /*!
     * @brief this function adds a movie to the user watch list
     * @param movie the movie to be added
     */
    void add_movie_user(const Movie& movie);
    /*!
     * @brief this function removes a movie from the user watch list
     * @param movie the movie to be removed
     */
    void remove_movie_user(const Movie &movie);
    /*!
     * @brief this function gets a list of the movies in the user's watchlist
     */
    DynamicVector<Movie> get_watchlist_user();

    /*!
     * @brief gives a like to a movie
     * @param movie the movie to be liked
     */
    void like_movie_user(const Movie &movie);

    /*!
     * @brief converts a string to lower characters
     * @param s the string
     * @return the string containing only lowered characters
     */
    std::string my_tolower(const std::string &s)const;
};

#endif //A5_6_GEORGERAPEANU_MOVIECONTROLLER_H
