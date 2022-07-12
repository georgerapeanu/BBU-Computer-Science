#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	this->mod = 1;
    this->__size = 0;
    this->elems = new TElem[this->mod];
    this->elems[0] = NULL_TELEM;
}/// BC: theta(1), WC: theta(1), TC:theta(1)

void Bag::resize() {
    int old_capacity = this->mod;
    this->mod *= 2;
    TElem* new_elems = new TElem[this->mod];

    for(int i = 0; i < this->mod; i++){
        new_elems[i] = NULL_TELEM;
    }

    for(int i = 0; i < old_capacity; i++){
        if(elems[i] == NULL_TELEM || elems[i] == DELETED_TELEM){
            continue;
        }
        for(int j = 0; j < this->mod; j++){
            if(new_elems[this->hash(elems[i], j)] == NULL_TELEM){
                new_elems[this->hash(elems[i], j)] = this->elems[i];
                break;
            }
        }
    }
    delete[] this->elems;
    this->elems = new_elems;
}/// BC: theta(new size), WC: theta(old size ^ 2), TC: O(old size ^ 2)

void Bag::add(TElem elem) {
	if(this->__size == this->mod){
        this->resize();
    }

    for(int i = 0;i < this->mod;i++){
        if(this->elems[this->hash(elem, i)] == NULL_TELEM || this->elems[this->hash(elem, i)] == DELETED_TELEM){
            this->elems[this->hash(elem, i)] = elem;
            break;
        }
    }
    this->__size++;
}/// BC: theta(1), WC: theta(size ^ 2), TC: O(size ^ 2)


bool Bag::remove(TElem elem) {
    for(int i = 0;i < this->mod;i++){
        if(this->elems[this->hash(elem, i)] == NULL_TELEM) {
            break;
        }
        if(this->elems[this->hash(elem, i)] == elem) {
            this->elems[this->hash(elem, i)] = DELETED_TELEM;
            this->__size--;
            return true;
        }
    }
	return false;
}/// BC: theta(1), WC: theta(size), TC: O(size)

bool Bag::search(TElem elem) const {
    for(int i = 0;i < this->mod;i++){
        if(this->elems[this->hash(elem, i)] == NULL_TELEM) {
            break;
        }
        if(this->elems[this->hash(elem, i)] == elem) {
            return true;
        }
    }
	return false;
}/// BC: theta(1), WC: theta(size), TC: O(size)

int Bag::nrOccurrences(TElem elem) const {
    int count = 0;
    for(int i = 0;i < this->mod;i++){
        if(this->elems[this->hash(elem, i)] == NULL_TELEM) {
            break;
        }
        if(this->elems[this->hash(elem, i)] == elem) {
            count++;
        }
    }
	return count;
}/// BC: theta(1), WC: theta(size), TC: O(size)


int Bag::size() const {
	return this->__size;
}/// BC: theta(1), WC: theta(1), TC: theta(1)

bool Bag::isEmpty() const {
	return this->size() == 0;
}/// BC: theta(1), WC: theta(1), TC: theta(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}/// BC: theta(1), WC: theta(1), TC: theta(1)

Bag::~Bag() {
	delete[] this->elems;
}/// BC: theta(size), WC: theta(size), TC: theta(size)

int Bag::hash1(int k) const {
    return ((unsigned int)k) % mod;
}/// BC: theta(1), WC: theta(1), TC: theta(1)

int Bag::hash2(int k) const {
    return (2 * ((unsigned int)k) + 79) % mod;
}/// BC: theta(1), WC: theta(1), TC: theta(1)

int Bag::hash(int k, int i) const {
    return (hash1(k) + 1LL * i * hash2(k)) % mod;
}/// BC: theta(1), WC: theta(1), TC: theta(1)