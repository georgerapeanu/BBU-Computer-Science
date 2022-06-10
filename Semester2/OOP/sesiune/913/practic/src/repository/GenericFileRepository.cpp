//
// Created by georgerapeanu on 09.06.2022.
//

#include "GenericFileRepository.h"
#include "AppException.h"
#include "Question.h"
#include "Participant.h"

template<class T>
GenericFileRepository<T>::GenericFileRepository(const std::string &filepath) {
    this->filepath = filepath;
    std::ifstream f(filepath);
    if(!f){
        throw AppException("File" + filepath + "invalid\n");
    }
    f.close();
}

template<class T>
void GenericFileRepository<T>::load() {
    std::ifstream f(filepath);
    this->entities.clear();
    T elem;
    while(f >> elem){
        this->entities.push_back(elem);
    }
    f.close();
}

template<class T>
void GenericFileRepository<T>::save() {
    std::ofstream g(filepath);
    for(auto it:entities){
        g << it << "\n";
    }
    g.close();
}

template<class T>
void GenericFileRepository<T>::add(T elem) {
    this->load();
    for(auto &repo_entity:this->entities){
        if(repo_entity == elem){
            throw AppException("Element with specified id already in repository");
        }
    }
    this->entities.push_back(elem);
    this->save();
}

template<class T>
std::vector<T> GenericFileRepository<T>::getAll(){
    this->load();
    return this->entities;
}

template<class T>
void GenericFileRepository<T>::update(T elem) {
    this->load();
    for(auto &repo_elem:this->entities){
        if(repo_elem == elem){
            repo_elem = elem;
            this->save();
            return ;
        }
    }
    throw AppException("Element with specified id doesn't exist");
}

template class GenericFileRepository<Participant>;
template class GenericFileRepository<Question>;