#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>

using namespace std;

FixedCapBiMap::FixedCapBiMap(int capacity) {
  if(capacity < 0){
    throw exception();
  }
  this->elements = new TElem[capacity];
  this->capacity = capacity;
  this->current_size = 0;
}

FixedCapBiMap::~FixedCapBiMap() {
  delete[] this->elements;
}

bool FixedCapBiMap::add(TKey c, TValue v){
  if(this->capacity == this->current_size){
    throw exception();
  }
  int cnt = 0;
	for(int i = 0;i < this->current_size;i++){
    if(this->elements[i].first == c){
      cnt++;
    }
  }
  if(cnt == 2){
    return false;
  }
  this->elements[this->current_size++] = make_pair(c, v);
  return true;
}

ValuePair FixedCapBiMap::search(TKey c) const{
  pair<TValue, TValue> ans(NULL_TVALUE, NULL_TVALUE); 

  for(int i = 0;i < this->current_size;i++){
    if(c == this->elements[i].first){
      if(ans.first == NULL_TVALUE){
        ans.first = this->elements[i].second;
      }else if(ans.second == NULL_TVALUE){
        ans.second = this->elements[i].second;
        break;
      }
    }
  }
  return ans;
}

bool FixedCapBiMap::remove(TKey c, TValue v){
  int pos = -1;
  for(int i = 0;i < this->current_size;i++){
    if(this->elements[i] == make_pair(c, v)){
      pos = i;
      break;
    }
  }
  if(pos == -1){
	  return false;
  }
  for(int i = pos;i + 1 < this->current_size;i++){
    this->elements[i] = this->elements[i + 1];
  }
  this->current_size--;
  return true;
}


int FixedCapBiMap::size() const {
	return this->current_size;
}

bool FixedCapBiMap::isEmpty() const{
	return this->current_size == 0;
}

bool FixedCapBiMap::isFull() const {
	return this->current_size == this->capacity;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}



