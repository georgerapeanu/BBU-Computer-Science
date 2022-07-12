/*!
 * @file Repository.cpp this file contains the implementation of Repository
 */

//
// Created by georgerapeanu on 21.03.2022.
//

#pragma once
#include "Repository.h"
#include "Movie.h"
#include <iostream>

template<class T>
Repository<T>::Repository() {
    this->entities = DynamicVector<T>();
}

template<class T>
Repository<T>::Repository(const Repository<T> &other) {
    this->entities = other.entities;
}

template<class T>
Repository<T>::~Repository() {
    ;
}

template<class T>
void Repository<T>::add(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            throw RepositoryException("Id already exists");
        }
    }
    this->entities.push_back(elem);
}

template<class T>
void Repository<T>::update(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            this->entities[i] = elem;
            return ;
        }
    }
    throw RepositoryException("Id doesn't exist");
}


template<class T>
void Repository<T>::remove(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            this->entities.remove(i);
            return ;
        }
    }
    throw RepositoryException("Id doesn't exist");
}

template<class T>
T Repository<T>::find(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            return this->entities[i];
        }
    }
    throw RepositoryException("Id doesn't exist");
}

template<class T>
DynamicVector<T> Repository<T>::get_all() {
    return this->entities;
}

template class Repository<Movie>;