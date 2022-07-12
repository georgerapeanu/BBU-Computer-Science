/*!
 * @file UI.h this file contains the model for an UI class
 */
//
// Created by georgerapeanu on 21.03.2022.
//

#ifndef A5_6_GEORGERAPEANU_UI_H
#define A5_6_GEORGERAPEANU_UI_H
#pragma once

#include "MovieController.h"

/*!
 * @brief this class contains the model for an ui class
 */
class UI{
    //! the movie controller
    MovieController& controller;

    std::vector<std::string> split_command(const std::string &s);

    /*!
     * @brief this function displays the information for a movie
     * @param movie
     */
    void display_movie(const Movie &movie)const;

    /*!
     * @brief this function displays the help for a section
     */
    void display_help(const std::vector<std::string> &help)const;

    /*!
     * @brief this function runs the admin interface
     */
    void run_admin();
    /*!
     * @brief this function runs the user interface
     */
    void run_user();

    /*!
     * @brief this function is responsible for handling the add for a movie
     * @param args the arguments for the add operation
     */
    void handle_add_admin(const std::vector<std::string> &args);

    /*!
     * @brief this function is responsible for handling the update for a movie
     * @param args the arguments for the update operation
     */
    void handle_update_admin(const std::vector<std::string> &args);
    /*!
     * @brief this function is responsible for handling the removing for a movie
     * @param args the arguments for the update operation
     */
    void handle_remove_admin(const std::vector<std::string> &args);

    /*!
     * @brief this function is responsible for getting the movies for an admin operation
     * @param args the arguments
     */
    void handle_get_movies_admin(const std::vector<std::string> &args);

    /*!
     * @brief this function is responsible for getting the movies for an user operation
     * @param args the arguments
     */
    void handle_get_movies_user(const std::vector<std::string> &args);

    /*!
     * @brief this function is responsible for removing a given movie from the watchlist
     * @param args the arguments
     */
    void handle_remove_movie_user(const std::vector<std::string> &args);

    /*!
    * @brief this function is responsible for getting the watchlist for an operation
    * @param args the arguments
    */
    void handle_get_watchlist_user(const std::vector<std::string> &args);

public:

    /*!
     * @brief the constructor of an UI instance
     * @param controller the movie controller to be used
     */
    UI(MovieController& controller);

    /*!
     * runs the ui
     */
    void run();
};

#endif //A5_6_GEORGERAPEANU_UI_H
