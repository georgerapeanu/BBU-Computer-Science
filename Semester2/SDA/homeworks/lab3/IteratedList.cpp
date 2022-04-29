
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"

IteratedList::IteratedList() {
  next = new int[1];
  elems = new TElem[1];
  capacity = 1;
  head = -1;
  free_head = 0;
  next[0] = -1;
  elems[0] = NULL_TELEM; 
}///BC: theta(1), WC: theta(1), TC: theta(1)

void IteratedList::change_capacity(int new_capacity){
  int* new_next = new int[new_capacity];
  int* new_elems = new int[new_capacity];

  for(int i = 0;i < new_capacity && i < capacity;i++){
    new_next[i] = next[i];
    new_elems[i] = elems[i];
  }

  for(int i = capacity;i < new_capacity;i++){
    new_next[i] = free_head;
    new_elems[i] = NULL_TELEM;
    free_head = i;
  }
  delete[] next;
  delete[] elems;
  next = new_next;
  elems = new_elems;
  capacity = new_capacity;
}/// BC: theta(new_capacity), WC: theta(new_capacity), TC: theta(new_capacity)
///Semi-undefined behavior if new_capacity < capacity

int IteratedList::allocate(){
  if(free_head == -1){
    this->change_capacity(2 * capacity);
  }
  int tmp = free_head;
  free_head = next[free_head];

  return tmp;
}///BC: theta(1), WC: theta(capacity), TC: O(capacity)

void IteratedList::deallocate(int node){
  next[node] = free_head;
  elems[node] = NULL_TELEM;
  free_head = node;
}///BC: theta(1), WC: theta(1), TC: theta(1)


int IteratedList::size() const {
	int answer = 0;

  for(int node = head;node != -1;node = next[node]){
    answer++;
  }
  return answer;
}///BC: theta(size), WC: theta(size), TC: theta(size)

bool IteratedList::isEmpty() const {
	return (head == -1);
}///BC: theta(1), WC: theta(1), TC: theta(1)

ListIterator IteratedList::first() const {
	return ListIterator(*this);
}

TElem IteratedList::getElement(ListIterator pos) const {
  return pos.getCurrent();
}///BC: theta(1), WC: theta(1), TC: theta(1)

TElem IteratedList::remove(ListIterator& pos) {
  if(!pos.valid()){
    throw std::exception();
  }
	
  if(pos.index == head){
    int tmp_node = head;
    TElem tmp_elem = elems[head];
    head = next[head];
    pos.index = head;
    this->deallocate(tmp_node);
    return tmp_elem;
  }

  for(int node = head;node != -1;node = next[node]){
    if(next[node] == pos.index){
      TElem tmp_elem = elems[pos.index];
      next[node] = next[next[node]];
      deallocate(pos.index);
      pos.index = next[node];
      return tmp_elem;
    }
  }

  throw std::exception();///not theoretically reachable
}///BC: theta(1), WC: theta(size), TC: O(size)

ListIterator IteratedList::search(TElem e) const{
  ListIterator node(*this);
	for(; node.valid(); node.next()){
    if(node.getCurrent() == e){
      return node;  
    }
  }
  return node;
}///BC: theta(1), WC: theta(size), TC: O(size)

TElem IteratedList::setElement(ListIterator pos, TElem e) {
	if(!pos.valid()){
    throw std::exception();
  }
  TElem tmp_elem = elems[pos.index];
  elems[pos.index] = e;
  return tmp_elem;
}///BC: theta(1), WC: theta(1), TC: theta(1)

void IteratedList::addToPosition(ListIterator& pos, TElem e) {
	if(!pos.valid()){
    throw std::exception();
  }
  int new_node = this->allocate();
  next[new_node] = next[pos.index];
  next[pos.index] = new_node;
  elems[new_node] = e;
  pos.next();

}///BC: theta(1), WC: theta(size), TC: O(size)

void IteratedList::addToEnd(TElem e) {
  if(head == -1){
    int new_node = this->allocate();
    head = new_node;
    elems[new_node] = e;
    next[new_node] = -1;
    return ;
  }
  int node;
  for(node = head;next[node] != -1;node = next[node]);
  int new_node = this->allocate();
  next[node] = new_node;
  next[new_node] = -1;
  elems[new_node] = e;
}///BC: theta(1), WC: theta(size), TC: O(size)
	
void IteratedList::addToBeginning(TElem e) {
  int new_node = this->allocate();
  next[new_node] = head;
  head = new_node;
  elems[new_node] = e;
}///BC: theta(1), WC: theta(size), TC: O(size)

IteratedList::~IteratedList() {
  delete[] next;
  delete[] elems;
}///BC: theta(size), WC: theta(size), TC: theta(size)
