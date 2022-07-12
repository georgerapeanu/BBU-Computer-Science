/*!
 * @file MemoryWatchlist.cpp this is a file containing the implementation for an in-memory watchlist
 */

//
// Created by georgerapeanu on 18.04.2022.
//

#pragma once
#include "MemoryWatchlist.h"
#include "Movie.h"
#include "Exceptions.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

template<class T>
MemoryWatchlist<T>::MemoryWatchlist() {
    this->entities = vector<T>();
}

template<class T>
MemoryWatchlist<T>::~MemoryWatchlist() {
    ;
}

template<class T>
void MemoryWatchlist<T>::add(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            throw RepositoryException("Id already exists");
        }
    }
    this->entities.push_back(elem);
    this->save();
}

template<class T>
void MemoryWatchlist<T>::update(const T &elem) {
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
void MemoryWatchlist<T>::remove(const T &elem) {
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
T MemoryWatchlist<T>::find(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            return this->entities[i];
        }
    }
    throw RepositoryException("Id doesn't exist");
}

template<class T>
vector<T> MemoryWatchlist<T>::get_all() {
    return this->entities;
}

template<class T>
void MemoryWatchlist<T>::save() const {
    ;
}

template<class T>
void MemoryWatchlist<T>::display() const {
    ;
}

template class MemoryWatchlist<Movie>;


