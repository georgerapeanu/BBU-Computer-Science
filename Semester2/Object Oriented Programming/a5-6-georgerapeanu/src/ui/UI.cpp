/*!
 * @file UI.cpp this file contains the UI class implementation
 */

//
// Created by georgerapeanu on 21.03.2022.
//

#pragma once
#include "UI.h"
#include <string>
#include "DynamicVector.h"
#include <iostream>
#include <stdlib.h>

UI::UI(const MovieController &controller) {
    this->controller = controller;
}

void UI::run_admin() {
    DynamicVector<std::string> help_display;
    help_display.push_back("===============ADMIN PORTAL================");
    help_display.push_back("add <title> <genre> <year> <likes> <trailer_link> -> adds a movie with the given parameters. there shouldn't be any other movie with the same title and year");
    help_display.push_back("update <title> <genre> <year> <likes> <trailer_link> -> updates the movie with the given title and year to have the new specified parameters");
    help_display.push_back("remove <title> <year> -> removes the movie with the given title and year");
    help_display.push_back("list -> prints a list containing all movies");
    help_display.push_back("logout -> logout of the admin account");
    help_display.push_back("help -> displays the help prompt");
    help_display.push_back("===========================================");
    display_help(help_display);
    while(true){
        std::string command;
        getline(std::cin, command);
        DynamicVector<std::string> args = split_command(command);
        try{
            if(args.size() > 0 && args[0] == "add"){
                handle_add_admin(args);
            }else if(args.size() > 0 && args[0] == "update"){
                handle_update_admin(args);
            }else if(args.size() > 0 && args[0] == "remove"){
                handle_remove_admin(args);
            }else if(args.size() > 0 && args[0] == "list"){
                handle_get_movies_admin(args);
            }else if(args.size() == 1 && args[0] == "help"){
                display_help(help_display);
            }else if(args.size() == 1 && args[0] == "logout"){
                break;
            }else{
                std::cout << "Invalid command!" << std::endl;
                display_help(help_display);
            }
        }catch(const AppException &exception){
            std::cout << exception.get_message() << std::endl;
            display_help(help_display);
        }
    }
}

void UI::run_user() {
    DynamicVector<std::string> help_display;
    help_display.push_back("================USER PORTAL================");
    help_display.push_back("get movies from <genre> -> gets all movies with given genre");
    help_display.push_back("remove movie <title> <year> -> remove the given movie from the watchlist");
    help_display.push_back("list -> prints all movies in a watchlist");
    help_display.push_back("logout -> logout of the admin account");
    help_display.push_back("help -> displays the help prompt");
    help_display.push_back("===========================================");
    display_help(help_display);
    while(true){
        std::string command;
        getline(std::cin, command);
        DynamicVector<std::string> args = split_command(command);
        try{
            if(args.size() > 3 && args[0] == "get" && args[1] == "movies" && args[2] == "from"){
                handle_get_movies_user(args);
            }else if(args.size() > 1 && args[0] == "remove" && args[1] == "movie"){
                handle_remove_movie_user(args);
            }else if(args.size() > 0 && args[0] == "list"){
                handle_get_watchlist_user(args);
            }else if(args.size() == 1 && args[0] == "help"){
                display_help(help_display);
            }else if(args.size() == 1 && args[0] == "logout"){
                break;
            }else{
                std::cout << "Invalid command!" << std::endl;
                display_help(help_display);
            }
        }catch(const AppException &exception){
            std::cout << exception.get_message() << std::endl;
            display_help(help_display);
        }
    }

}

void UI::run() {
    DynamicVector<std::string> help_display;
    help_display.push_back("================LOGIN PORTAL================");
    help_display.push_back("login user -> logins as user account");
    help_display.push_back("login admin -> logins as administrator account");
    help_display.push_back("exit -> exits the application");
    help_display.push_back("help -> displays the help prompt");
    help_display.push_back("============================================");

    display_help(help_display);
    while(true){
        std::string command;
        getline(std::cin, command);
        DynamicVector<std::string> args = split_command(command);
        if(args.size() == 2 && args[0] == "login" && args[1] == "user"){
            run_user();
        }else if(args.size() == 2 && args[0] == "login" && args[1] == "admin"){
            run_admin();
        }else if(args.size() == 1 && args[0] == "exit"){
            break;
        }else if(args.size() == 1 && args[0] == "help"){
            display_help(help_display);
        }else{
            std::cout << "Invalid command!" << std::endl;
            display_help(help_display);
        }
    }
}

DynamicVector<std::string> UI::split_command(const std::string &s) {
    DynamicVector<std::string> ans;
    std::string curr = "";
    for(unsigned int i = 0;i < s.size();i++){
        if(s[i] != ' ' && s[i] != '\n' && s[i] != '\t' && s[i] != '\r'){
            curr += s[i];
        }else{
            if(!curr.empty()){
                ans.push_back(curr);
            }
            curr = "";
        }
    }
    if(!curr.empty()){
        ans.push_back(curr);
    }
    return ans;
}

void UI::handle_add_admin(const DynamicVector<std::string> &args) {
    if(args.size() != 6){
        throw UIException("arguments are wrong for given command");
    }
    try {
        std::string title = args[1];
        std::string genre = args[2];
        int year = std::stoi(args[3]);
        int likes = std::stoi(args[4]);
        std::string trailer_link = args[5];
        this->controller.add_movie_admin(title, genre, year, likes, trailer_link);
    }catch(const std::invalid_argument &exception){
        throw UIException("arguments are wrong for given command");
    }
}

void UI::handle_update_admin(const DynamicVector<std::string> &args) {
    if(args.size() != 6){
        throw UIException("arguments are wrong for given command");
    }

    try{
        std::string title = args[1];
        std::string genre = args[2];
        int year = std::stoi(args[3]);
        int likes = std::stoi(args[4]);
        std::string trailer_link = args[5];
        this->controller.update_movie_admin(title, genre, year, likes, trailer_link);
    }catch(const std::invalid_argument &exception){
        throw UIException("arguments are wrong for given command");
    }
}

void UI::handle_remove_admin(const DynamicVector<std::string> &args) {
    if(args.size() != 3){
        throw UIException("arguments are wrong for given command");
    }
    try {
        std::string title = args[1];
        int year = std::stoi(args[2]);
        this->controller.remove_movie_admin(title, year);
    }catch(const std::invalid_argument &exception){
        throw UIException("arguments are wrong for given command");
    }
}

void UI::handle_get_movies_admin(const DynamicVector<std::string> &args) {
    if(args.size() != 1){
        throw UIException("arguments are wrong for given command");
    }
    DynamicVector<Movie> movies = this->controller.get_all_movies_admin();
    for(unsigned int i = 0;i < movies.size();i++){
        display_movie(movies[i]);
    }
}

void UI::handle_get_movies_user(const DynamicVector<std::string> &args) {
    if(args.size() != 4){
        throw UIException("arguments are wrong for given command");
    }
    DynamicVector<Movie> movies = this->controller.get_movies_user(args[3]);
    if(movies.size() == 0){
        throw UIException("no movies for given genre");
    }
    unsigned int current = 0;
    std::string command;

    while(true){
        std::string command = "firefox " + movies[current].get_trailer_link();
        system(command.c_str());
        display_movie(movies[current]);
        try_again:
        std::cout << "add to watchlist?(yes/no/stop)\n";
        getline(std::cin, command);
        try{
            if(command == "yes" || command == "y"){
                this->controller.add_movie_user(movies[current]);
            }else if(command == "no" || command == "n"){
                ;
            }else if(command == "stop" || command == "s" || command == "x"){
                break;
            }else{
                throw UIException("option not available");
            }
        }catch(const AppException &exception){
            std::cout << exception.get_message() << std::endl;
            goto try_again;
        }
        current++;
        current = (current >= movies.size() ? 0:current);
    }
}

void UI::handle_remove_movie_user(const DynamicVector<std::string> &args) {
    if(args.size() != 4){
        throw UIException("arguments are wrong for given command");
    }
    Movie movie;
    try{
        movie = this->controller.get_movie_user(args[2], std::stoi(args[3]));
    }catch(const std::invalid_argument &exception){
        throw UIException("arguments are wrong for given command");
    }
    this->controller.remove_movie_user(movie);
    std::cout << "Like movie?(yes/no)" << std::endl;
    std::string ans;
    while(true){
        getline(std::cin, ans);
        if(ans == "yes" || ans == "y"){
            this->controller.like_movie_user(movie);
            break;
        }else if(ans == "no" || ans == "n"){
            break;
        }else{
            std::cout << "Invalid option" << std::endl;
        }
    }
}

void UI::handle_get_watchlist_user(const DynamicVector<std::string> &args) {
    if(args.size() != 1){
        throw UIException("arguments are wrong for given command");
    }
    DynamicVector<Movie> movies = this->controller.get_watchlist_user();
    for(unsigned int i = 0;i < movies.size();i++){
        display_movie(movies[i]);
    }
}

void UI::display_help(const DynamicVector<std::string> &help) const {
    for(unsigned int i = 0;i < help.size();i++){
        std::cout << help[i] << std::endl;
    }
}

void UI::display_movie(const Movie &movie) const {
    std::cout << movie.get_title() << " ";
    std::cout << movie.get_genre() << " ";
    std::cout << movie.get_year() << " ";
    std::cout << movie.get_likes() << " ";
    std::cout << movie.get_trailer_link() << std::endl;
}
