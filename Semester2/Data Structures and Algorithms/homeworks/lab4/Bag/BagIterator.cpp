#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->position = 0;
    while(this->position < this->bag.mod && (this->bag.elems[this->position] == NULL_TELEM || this->bag.elems[this->position] == DELETED_TELEM)){
        this->position++;
    }
}/// BC: theta(1), WC: theta(size), TC: O(size)

void BagIterator::first() {
    this->position = 0;
    while(this->position < this->bag.mod && (this->bag.elems[this->position] == NULL_TELEM || this->bag.elems[this->position] == DELETED_TELEM)){
        this->position++;
    }
}/// BC: theta(1), WC: theta(size), TC: O(size)


void BagIterator::next() {
	if(!this->valid()){
        throw exception();
    }
    this->position++;
    while(this->position < this->bag.mod && (this->bag.elems[this->position] == NULL_TELEM || this->bag.elems[this->position] == DELETED_TELEM)){
        this->position++;
    }
}/// BC: theta(1), WC: theta(size), TC: O(size)


bool BagIterator::valid() const {
	return (this->position < this->bag.mod);
}/// BC: theta(1), WC: theta(size), TC: O(size)


TElem BagIterator::getCurrent() const
{
	if(!this->valid()){
        throw exception();
    }
	return this->bag.elems[this->position];
}

void BagIterator::previous() {
    if(!this->valid()){
        throw exception();
    }
    this->position--;
    while(this->position >= 0 && (this->bag.elems[this->position] == NULL_TELEM || this->bag.elems[this->position] == DELETED_TELEM)){
        this->position--;
    }
    if(this->position < 0){
        this->position = this->bag.mod;
    }
}
/// BC: theta(1), WC: theta(size), TC: O(size)
