/*!
 * @file FileRepository.cpp this file contains the implementation for a file repository
 */

//
// Created by georgerapeanu on 18.04.2022.
//

#pragma once
#include "FileRepository.h"
#include "Movie.h"
#include <vector>
#include <string>
#include <fstream>
#include "Exceptions.h"

using namespace std;

template<class T>
FileRepository<T>::FileRepository(const string &file_path) {
    this->file_path = file_path;
    this->entities = vector<T>();
}

template<class T>
FileRepository<T>::~FileRepository() {
    ;
}

template<class T>
void FileRepository<T>::add(const T &elem) {
    this->load();
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            throw RepositoryException("Id already exists");
        }
    }
    this->entities.push_back(elem);
    this->save();
}

template<class T>
void FileRepository<T>::update(const T &elem) {
    this->load();
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
void FileRepository<T>::remove(const T &elem) {
    this->load();
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
T FileRepository<T>::find(const T &elem) {
    this->load();
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            return this->entities[i];
        }
    }
    throw RepositoryException("Id doesn't exist");
}

template<class T>
vector<T> FileRepository<T>::get_all() {
    this->load();
    return this->entities;
}

template<class T>
void FileRepository<T>::save() {
    ofstream fout(this->file_path);
    for(const auto &entity:entities){
        fout << entity << endl;
    }
    fout.close();
    this->entities = vector<T>();
}

template<class T>
void FileRepository<T>::load() {
    this->entities = vector<T>();
    ifstream fin(this->file_path);
    T entity;
    try{
        while(fin >> entity){
            entities.push_back(entity);
        }
    }catch(const DomainException &ex){
        if(entity != T()){
            throw ex;
        }
    }

    fin.close();
}

template class FileRepository<Movie>;