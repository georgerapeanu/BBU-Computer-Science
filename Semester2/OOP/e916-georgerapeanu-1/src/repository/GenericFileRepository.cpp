//
// Created by georgerapeanu on 12.06.2022.
//

#include "GenericFileRepository.h"
#include "AppException.h"
#include "User.h"
#include "Question.h"
#include "Answer.h"
#include <fstream>

template<class T>
GenericFileRepository<T>::GenericFileRepository(const std::string &filepath):filepath(filepath) {
    std::ifstream f(filepath);
    if(!f){
        throw AppException("File " + filepath + " doesn't exist");
    }

    this->entities = {};
    T entity;

    while(f >> entity){
        this->entities.push_back(entity);
    }
    f.close();
}

template<class T>
GenericFileRepository<T>::~GenericFileRepository() {
    std::ofstream g(this->filepath);
    for(auto entity:entities){
        g << entity << "\n";
    }
    g.close();
}

template<class T>
void GenericFileRepository<T>::add(const T &entity) {
    for(const auto& repo_entity:this->entities){
        if(repo_entity.getId() == entity.getId()){
            throw AppException("Entity with specified id already exists");
        }
    }
    this->entities.push_back(entity);
}

template<class T>
void GenericFileRepository<T>::update(const T &entity) {
    for(auto& repo_entity:this->entities){
        if(repo_entity.getId() == entity.getId()){
            repo_entity = entity;
            return ;
        }
    }
    throw AppException("Entity with specified id doesn't exist");
}

template<class T>
T GenericFileRepository<T>::getById(const T& entity) {
    for(const auto& repo_entity:entities){
        if(repo_entity.getId() == entity.getId()){
            return repo_entity;
        }
    }
    throw AppException("Entity with specified id doesn't exist");
}

template<class T>
std::vector<T> GenericFileRepository<T>::getAll() {
    return this->entities;
}


template class GenericFileRepository<User>;
template class GenericFileRepository<Question>;
template class GenericFileRepository<Answer>;

