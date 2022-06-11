//
// Created by georgerapeanu on 11.06.2022.
//

#include "FileRepository.h"
#include "AppException.h"
#include "Answer.h"
#include "Question.h"
#include "User.h"

#include <fstream>

template<class T>
FileRepository<T>::FileRepository(const std::string& filepath) {
    this->filepath = filepath;
    std::ifstream f(filepath);

    if(!f){
        throw AppException("File " + filepath + " doesn't exist");
    }
    f.close();
}


template<class T>
void FileRepository<T>::add(T entity) {
    this->load();
    for(auto &it:entities){
        if(it.getId() == entity.getId()){
            throw AppException("Entity with specified id already exists");
        }
    }
    entities.push_back(entity);
    this->save();
}

template<class T>
void FileRepository<T>::update(T entity) {
    this->load();
    for(auto &it:entities){
        if(it.getId() == entity.getId()){
            it = entity;
            this->save();
            return ;
        }
    }
    throw AppException("Entity with specified id doesn't exist");
}

template<class T>
std::vector<T> FileRepository<T>::getAll() {
    this->load();
    return this->entities;
}

template<class T>
T FileRepository<T>::getById(const T& entity) {
    this->load();
    for(auto &it:entities){
        if(entity.getId() == it.getId()){
            return it;
        }
    }
    throw AppException("Entity with specified id doesn't exist");
}

template<class T>
void FileRepository<T>::load() {
    this->entities.clear();
    std::ifstream  f(this->filepath);

    T tmp;

    while(f >> tmp){
        this->entities.push_back(tmp);
    }
    f.close();
}

template<class T>
void FileRepository<T>::save() {
    std::ofstream  g(this->filepath);

    for(auto &it:this->entities){
        g << it << "\n";
    }

    g.close();
    this->entities.clear();
}

template class FileRepository<User>;
template class FileRepository<Question>;
template class FileRepository<Answer>;