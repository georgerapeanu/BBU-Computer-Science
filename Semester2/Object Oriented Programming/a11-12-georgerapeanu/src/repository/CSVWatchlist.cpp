/*!
 * @file CSVWatchlist.cpp this file contains the implementation for the CSV watchlist
 */

//
// Created by georgerapeanu on 18.04.2022.
//

#pragma once
#include "CSVWatchlist.h"
#include "Movie.h"
#include "Exceptions.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

template<class T>
CSVWatchlist<T>::CSVWatchlist(const string &file_path) {
    this->file_path = file_path;
    this->entities = vector<T>();
}

template<class T>
CSVWatchlist<T>::~CSVWatchlist() {
    ;
}

template<class T>
void CSVWatchlist<T>::add(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            throw RepositoryException("Id already exists");
        }
    }
    this->entities.push_back(elem);
    this->save();
}

template<class T>
void CSVWatchlist<T>::update(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            this->entities[i] = elem;
            this->save();
            return ;
        }
    }
    throw RepositoryException("Id doesn't exist");
}


template<class T>
void CSVWatchlist<T>::remove(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            this->entities.erase(this->entities.begin() + i);
            this->save();
            return ;
        }
    }
    throw RepositoryException("Id doesn't exist");
}

template<class T>
T CSVWatchlist<T>::find(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            return this->entities[i];
        }
    }
    throw RepositoryException("Id doesn't exist");
}

template<class T>
vector<T> CSVWatchlist<T>::get_all() {
    return this->entities;
}

template<class T>
void CSVWatchlist<T>::save() const {
    ofstream fout(this->file_path);
    for(const Movie &entity:entities){
        fout << entity.get_title() << ",";
        fout << entity.get_genre() << ",";
        fout << entity.get_year() << ",";
        fout << entity.get_likes() << ",";
        fout << entity.get_trailer_link() << endl;
    }
    fout.close();
}

template<class T>
void CSVWatchlist<T>::display() const {
    system(("libreoffice " + this->file_path).c_str());
}

template class CSVWatchlist<Movie>;
