//! @file DynamicVector.cpp this file contains the implementation for DynamicVector

//
// Created by georgerapeanu on 21.03.2022.
//
#pragma once
#include "DynamicVector.h"
#include "Exceptions.h"
#include "Movie.h"
#include <algorithm>
#include <string>

template<class T>
void DynamicVector<T>::change_capacity(unsigned int capacity){
    T* tmp_elems = new T[capacity];
    for(unsigned int i = 0;i < this->_size && i < capacity;i++){
        tmp_elems[i] = this->elems[i];
    }
    delete[] this->elems;
    this->elems = tmp_elems;
    this->capacity = capacity;
    this->_size = std::min(this->_size, capacity);
}

template<class T>
DynamicVector<T>::DynamicVector(){
    this->_size = 0;
    this->capacity = 1;
    this->elems = new T[1];
}

template<class T>
DynamicVector<T>::DynamicVector(unsigned int _size){
    this->_size = _size;
    this->capacity = std::max(_size, (unsigned int)1);
    this->elems = new T[_size];
    for(unsigned int i = 0;i < this->_size;i++){
        this->elems[i] = T();
    }
}

template<class T>
DynamicVector<T>::DynamicVector(unsigned int _size, T value){
    this->_size = _size;
    this->capacity = std::max(_size, (unsigned int)1);
    this->elems = new T[_size];
    for(unsigned int i = 0;i < this->_size;i++){
        this->elems[i] = value;
    }
}

template<class T>
DynamicVector<T>::DynamicVector(const DynamicVector<T> &other){
    this->_size = other._size;
    this->capacity = other.capacity;
    this->elems = new T[other.capacity];
    for(int i = 0;i < other.capacity;i++){
        this->elems[i] = other.elems[i];
    }
}

template<class T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector &other) {
    this->_size = other._size;
    this->capacity = other.capacity;
    delete[] this->elems;
    this->elems = new T[other.capacity];
    for(int i = 0;i < other.capacity;i++){
        this->elems[i] = other.elems[i];
    }
    return *this;
}

template<class T>
DynamicVector<T>::~DynamicVector(){
    delete[] this->elems;
}

template<class T>
T& DynamicVector<T>::operator [](unsigned int position){
    if(position >= this->_size){
        throw DynamicVectorException("position is outside of vector");
    }
    return this->elems[position];
}

template<class T>
void DynamicVector<T>::push_back(T elem){
    if(this->capacity == this->_size){
        change_capacity(this->capacity << 1);
    }
    this->elems[this->_size++] = elem;
}

template<class T>
void DynamicVector<T>::pop_back(){
    if(this->_size == 0){
        throw DynamicVectorException("vector is empty");
    }
    this->_size--;
}

template<class T>
T& DynamicVector<T>::back(){
    if(this->_size == 0){
        throw DynamicVectorException("vector is empty");
    }
    return this->elems[this->_size - 1];
}

template<class T>
unsigned int DynamicVector<T>::size()const{
    return this->_size;
}

template<class T>
void DynamicVector<T>::resize(unsigned int _size){
    this->change_capacity(_size);
    this->_size = _size;
}

template<class T>
void DynamicVector<T>::remove(unsigned int position) {
    if(position >= this->_size){
        throw DynamicVectorException("position is outside of vector");
    }
    for(unsigned int i = position;i + 1 < this->_size;i++){
        this->elems[i] = this->elems[i + 1];
    }
    this->_size--;
}

template<class T>
T DynamicVector<T>::operator[](unsigned int position) const {
    if(position >= this->_size){
        throw DynamicVectorException("position is outside of vector");
    }
    return this->elems[position];
}

template<class T>
bool DynamicVector<T>::operator==(const DynamicVector<T> &other) const {
    if(this->size() != other.size()){
        return false;
    }
    for(int i = 0;i < this->size();i++){
        if(this->elems[i] != other.elems[i]){
            return false;
        }
    }
    return true;
}

template<class T>
bool DynamicVector<T>::operator!=(const DynamicVector<T> &other) const {
    return !(*this == other);
}

template class DynamicVector<Movie>;
template class DynamicVector<std::string>;