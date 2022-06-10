//
// Created by georgerapeanu on 08.06.2022.
//

#include "GeneralFileRepository.h"
#include <fstream>
#include "Exceptions.h"
#include "User.h"
#include "Issue.h"

template<class T>
void GeneralFileRepository<T>::save() {
    std::ofstream g(this->filepath);
    if(!g){
        throw AppException("File " + this->filepath + " doesn't exist");
    }

    for(auto &entity:this->entities){
        g << entity << "\n";
    }

    g.close();
    this->entities.clear();
}

template<class T>
void GeneralFileRepository<T>::load() {
    std::ifstream f(this->filepath);
    if(!f){
        throw AppException("File " + this->filepath + " doesn't exist");
    }
    this->entities.clear();

    T entity;

    while(f >> entity){
        this->entities.push_back(entity);
    }

    f.close();
}

template<class T>
GeneralFileRepository<T>::GeneralFileRepository(const std::string &filepath) : filepath(filepath) {
    this->entities = {};
    this->load();
}

template<class T>
void GeneralFileRepository<T>::add(const T &entity) {
    this->load();
    for(auto &repo_entity:this->entities){
        if(entity == repo_entity){
            throw AppException("Entity with given id already exists");
        }
    }
    this->entities.push_back(entity);
    this->save();
}

template<class T>
void GeneralFileRepository<T>::remove(const T &entity) {
    this->load();
    bool found = false;
    for(int i = 0; i < (int)entities.size();i++){
        if(entity == entities[i]){
            found = true;
            for(int j = i + 1;j < (int)entities.size();j++){
                entities[j - 1] = entities[j];
            }
            entities.pop_back();
            break;
        }
    }
    if(!found){
        throw AppException("No such entity can be removed");
    }
    this->save();
}

template<class T>
void GeneralFileRepository<T>::update(const T &entity) {
    this->load();
    bool found = false;
    for(auto &repo_entity:this->entities){
        if(entity == repo_entity){
            found = true;
            repo_entity = entity;
            break;
        }
    }
    if(!found){
        throw AppException("No such entity can be updated");
    }
    this->save();
}

template<class T>
std::vector<T> GeneralFileRepository<T>::getAll() {
    this->load();
    return this->entities;
}

template<class T>
T GeneralFileRepository<T>::get(const T& entity) {
    this->load();
    for(auto &repo_entity:this->entities){
        if(entity == repo_entity){
            return repo_entity;
        }
    }
    throw AppException("No such entity exists");
}

template class GeneralFileRepository<User>;
template class GeneralFileRepository<Issue>;