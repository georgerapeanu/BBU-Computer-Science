#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c){
  this->index = 0;
}///best case theta(1), worst case theta(1), average case theta(1)

void BagIterator::first() {
  this->index = 0;
}///best case theta(1), worst case theta(1), average case theta(1)

void BagIterator::next() {
  if(this->index >= this->bag.size()){
    throw exception();
  }
  this->index++;
}///best case theta(1), worst case theta(1), average case theta(1)



bool BagIterator::valid() const {
	return (this->index < this->bag.size());
}///best case theta(1), worst case theta(1), average case theta(1)



TElem BagIterator::getCurrent() const{
	if(this->valid() == false){
    throw exception();
  }
  return this->bag.u[this->bag.p[this->index]];
}
