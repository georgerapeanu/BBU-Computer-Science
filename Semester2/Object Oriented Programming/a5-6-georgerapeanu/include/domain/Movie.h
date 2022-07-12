/*!
 * @file Movie.h this file contains the model for the Movie class
 */

//
// Created by georgerapeanu on 19.03.2022.
//

#ifndef A5_6_GEORGERAPEANU_MOVIE_H
#define A5_6_GEORGERAPEANU_MOVIE_H
#pragma once
#include <string>
/*!
 * The Movie class model
 */
class Movie{
    private:

    //! the title of the movie
    std::string title;
    //! the genre of the movie
    std::string genre;
    //! the year of the movie
    int year;
    //! the number of likes of the movie
    int likes;
    //! the link to the movie trailer
    std::string trailer_link;

    public:

    //! default constructor for an Movie instance
    Movie();
    /*!
     * copy constructor for an Movie instance
     * @param other the other movie instance who's attributes are copied.
     */
    Movie(const Movie &other);
    /*!
     * Constructor with full params.
     * @param title the movie title
     * @param genre the movie genre
     * @param year the year in which the movie was released
     * @param likes the number of likes the movie has
     * @param trailer_link a link to the trailer of the movie
     */
    Movie(const std::string &title, const std::string &genre, const int &year, const int &likes, const std::string &trailer_link);

    /*!
     * @brief gets the title of the movie
     * @return the title of the movies
     */
    std::string get_title()const;
    /*!
     * @brief gets the genre of the movie
     * @return the genre of the movie
     */
    std::string get_genre()const;
    /*!
     * @brief gets the year of the movie
     * @return the year in which the movie was released
     */
    int get_year()const;
    /*!
     * @brief gets the number of likes of the movie
     * @return the number of likes that the movie has
     */
    int get_likes()const;
    /*!
     * @brief gets the link to the trailer
     * @return the link to the movie
     */
    std::string get_trailer_link()const;

    /*!
     * @brief sets the title of the movie
     * @param title the new title of the movie
     */
    void set_title(const std::string &title);
    /*!
     * @brief sets the genre of the movie
     * @param genre the new genre of the movie
     */
    void set_genre(const std::string &genre);
    /*!
     * @brief sets the year of the movie
     * @param year the new year of the movie
     */
    void set_year(int year);
    /*!
     * @brief sets the number of likes of the movie
     * @param likes the nw likes of the movie
     */
    void set_likes(int likes);
    /*!
     * @brief set the trailer link
     * @param trailer_link  the new trailer link of the movie
     */
    void set_trailer_link(const std::string &trailer_link);

    /*!
     * @brief this function returns a string that will correspond to the id of the movie
     * @return the id of the movie
     */
    std::string get_id()const;
    /*!
     * @brief equality operator between movies
     * @param other the other movie
     * @return true if they are the same, false otherwise
     */
    bool operator == (const Movie &other)const;
    /*!
       * @brief not equal operator between movies
       * @param other the other movie
       * @return false if they are the same, true otherwise
       */
    bool operator != (const Movie &other)const;
};

#endif //A5_6_GEORGERAPEANU_MOVIE_H
