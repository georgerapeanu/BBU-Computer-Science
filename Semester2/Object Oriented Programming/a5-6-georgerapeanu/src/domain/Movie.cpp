//! @file Movie.cpp this file contains the implementation for the Movie class

//
// Created by georgerapeanu on 21.03.2022.
//
#pragma once
#include "Movie.h"
#include <sstream>
    //! default constructor for an Movie instance
Movie::Movie(){
    this->genre = "";
    this->title = "";
    this->likes = 0;
    this->trailer_link = "";
    this->year = 0;
}

Movie::Movie(const Movie &other){
    this->genre = other.genre;
    this->title = other.title;
    this->likes = other.likes;
    this->trailer_link = other.trailer_link;
    this->year = other.year;
}

Movie::Movie(const std::string &title, const std::string &genre, const int &year, const int &likes, const std::string &trailer_link){
    this->genre = genre;
    this->title = title;
    this->likes = likes;
    this->trailer_link = trailer_link;
    this->year = year;
}

std::string Movie::get_title() const {
    return this->title;
}

std::string Movie::get_genre() const {
    return this->genre;
}

int Movie::get_year() const {
    return this->year;
}

int Movie::get_likes() const {
    return this->likes;
}

std::string Movie::get_trailer_link() const {
    return this->trailer_link;
}

void Movie::set_title(const std::string &title){
    this->title = title;
}
void Movie::set_genre(const std::string &genre){
    this->genre = genre;
}

void Movie::set_year(int year){
    this->year = year;
}

void Movie::set_likes(int likes){
    this->likes = likes;
}

void Movie::set_trailer_link(const std::string &trailer_link){
    this->trailer_link = trailer_link;
}

std::string Movie::get_id() const {
    std::ostringstream  id;
    id << title;
    id << "###";
    id << year;
    return id.str();
}

bool Movie::operator==(const Movie &other) const {
    return  this->title == other.title &&
            this->genre == other.genre &&
            this->likes == other.likes &&
            this->year == other.year &&
            this->trailer_link == other.trailer_link;
}

bool Movie::operator!=(const Movie &other) const {
    return !(*this == other);
}
