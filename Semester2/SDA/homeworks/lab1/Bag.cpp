#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

Bag::Bag() {
  this->u = new int[1];
  this->capacity_u = 1;
  this->size_u = 0;
  this->p = new int[1];
  this->capacity_p = 1;
  this->size_p = 0;
}


void Bag::add(TElem elem) {
  int index = -1;
  for(int i = 0;i < this->size_u;i++){
    if(this->u[i] == elem){
      index = i;
      break;
    }
  }
  if(index == -1){
    if(this->size_u == this->capacity_u){
      TElem* new_u = new int[this->capacity_u * 2];
      for(int i = 0; i < this->size_u; i++) {
        new_u[i] = this->u[i];
      }
      delete[] this->u;
      this->u = new_u;
      this->capacity_u *= 2;
    }
    this->u[this->size_u++] = elem;
    index = this->size_u - 1;
  }

  if(this->size_p == this->capacity_p){
    TElem* new_p = new int[this->capacity_p * 2];
    for(int i = 0;i < this->size_p;i++){
      new_p[i] = p[i];
    }
    delete[] this->p;
    this->p = new_p;
    this->capacity_p *= 2;
  }
  this->p[this->size_p++] = index;
}/// best case: theta(1), worst case theta(number of elements + number of distinct elements), average case: theta(number of distinct elements)


bool Bag::remove(TElem elem) {
  int first_index = -1;
  int last_index = -1;
	for(int i = 0;i < this->size_p;i++){
    if(this->u[this->p[i]] == elem){
      if(first_index == -1){
        first_index = i;
      }
      last_index = i;
    }
  }
  if(last_index == -1){
    return false; 
  }
  for(int i = last_index;i + 1 < this->size_p;i++){
    this->p[i] = this->p[i + 1];
  }
  this->size_p--;
  
  if(last_index == first_index){ ///value elem no longer appears at all
    int u_index = -1;
    for(int i = 0;i < this->size_u;i++){
      if(this->u[i] == elem){
        u_index = i;
        break;
      }
    }
    for(int i = u_index;i + 1 < this->size_u;i++){
      this->u[i] = this->u[i + 1];
    }
    this->size_u--;
    for(int i = 0;i < this->size_p;i++){
      if(this->p[i] > u_index){
        this->p[i]--;
      }
    }
  }
  return true;
}/// Best case theta(number of elements), worst case theta(number of elements + number of distinct elements), average case theta(number of elements)


bool Bag::search(TElem elem) const {
	for(int i = 0;i < this->size_p;i++){
    if(this->u[this->p[i]] == elem){
      return true;
    }
  }
  return false; 
}///Best case: theta(number of elements), worst case theta(number of elements), average case theta(number of elements)

int Bag::nrOccurrences(TElem elem) const {
	int count = 0;

  for(int i = 0;i < this->size_p;i++){
    if(this->u[this->p[i]] == elem){
      count++;
    }
  }

  return count; 
}


int Bag::size() const {
	return this->size_p;
}


bool Bag::isEmpty() const {
	return (this->size_p == 0);
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
  delete[] this->p;
  delete[] this->u;
}

