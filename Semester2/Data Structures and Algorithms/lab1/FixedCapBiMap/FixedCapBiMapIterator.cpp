#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d):map(d)
{
  this->index = 0;
}


void FixedCapBiMapIterator::first() {
  this->index = 0;
}


void FixedCapBiMapIterator::next() {
  if(this->index >= this->map.size()){
    throw exception();
  }
  this->index++;
}


TElem FixedCapBiMapIterator::getCurrent(){
  if(this->index >= this->map.size()){
    throw exception();
  }
	return this->map.elements[this->index];
}


bool FixedCapBiMapIterator::valid() const {
	return this->index < this->map.size();
}



