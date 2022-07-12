#include "SetIterator.h"
#include "Set.h"
#include "stdlib.h"
#include <exception>


SetIterator::SetIterator(const Set& m) : set(m)
{
  this->current = set.head;
}///BC: theta(1), WC: theta(1), TC: theta(1)


void SetIterator::first() {
  this->current = this->set.head;
}///BC: theta(1), WC: theta(1), TC: theta(1)

void SetIterator::next() {
	if(this->current == NULL){
    throw std::exception();
  }
  this->current = this->current->next;
}///BC: theta(1), WC: theta(1), TC: theta(1)


TElem SetIterator::getCurrent()
{
	
	if(this->current == NULL){
    throw std::exception();
  }
  return this->current->elem;
}///BC: theta(1), WC: theta(1), TC: theta(1)

bool SetIterator::valid() const {
	return (this->current != NULL);
}



