/*!
 * @file Repository.cpp this file contains the implementation of Repository
 */

//
// Created by georgerapeanu on 21.03.2022.
//

#pragma once
#include "MemoryRepository.h"
#include "Movie.h"
#include <iostream>

using namespace std;

template<class T>
MemoryRepository<T>::MemoryRepository() {
    this->entities = vector<T>();
}

template<class T>
MemoryRepository<T>::~MemoryRepository() {
    ;
}

template<class T>
void MemoryRepository<T>::add(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            throw RepositoryException("Id already exists");
        }
    }
    this->entities.push_back(elem);
}

template<class T>
void MemoryRepository<T>::update(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            this->entities[i] = elem;
            return ;
        }
    }
    throw RepositoryException("Id doesn't exist");
}


template<class T>
void MemoryRepository<T>::remove(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            this->entities.erase(this->entities.begin() + i);
            return ;
        }
    }
    throw RepositoryException("Id doesn't exist");
}

template<class T>
T MemoryRepository<T>::find(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            return this->entities[i];
        }
    }
    throw RepositoryException("Id doesn't exist");
}

template<class T>
vector<T> MemoryRepository<T>::get_all() {
    return this->entities;
}

template class MemoryRepository<Movie>;