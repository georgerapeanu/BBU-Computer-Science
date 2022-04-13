#include "Set.h"
#include "SetIterator.h"
#include <stdlib.h>

Set::Set() {
  this->head=NULL;
}


bool Set::add(TElem elem) {
  node_t* tmp = this->head;

  while(tmp != NULL){
    if(tmp->elem == elem){
      return false;
    }
    tmp = tmp->next;
  }
  
  node_t* new_node = new node_t();
  new_node->next = this->head;
  new_node->elem = elem;
  this->head = new_node;

	return true;
}///BC: theta(1), WC: theta(size of set), TC: O(size set)


bool Set::remove(TElem elem) {
  node_t* prev_tmp = NULL;
  node_t* tmp = this->head;

  while(tmp != NULL){
    if(tmp->elem == elem){
      if(prev_tmp != NULL){
        prev_tmp->next = tmp->next;
        delete tmp;
      }else{
        this->head = tmp->next;
        delete tmp;
      }
      return true;
    }
    prev_tmp = tmp;
    tmp = tmp->next;
  }
  
	return false;
}///BC: theta(1), WC: theta(size of set), TC: O(size of set)

bool Set::search(TElem elem) const {
  node_t* tmp = this->head;

  while(tmp != NULL){
    if(tmp->elem == elem){
      return true;
    }
    tmp = tmp->next;
  }

  return false;
}///BC: theta(1), WC: theta(size of set), TC: O(size of set)


int Set::size() const {
  int ans = 0;
  node_t* tmp = this->head;

  while(tmp != NULL){
    ans++;
    tmp = tmp->next;
	}
  
  return ans;
}///BC: theta(size of set), WC: theta(size of set), TC: theta(size of set)


bool Set::isEmpty() const {
	return this->head == NULL;
}///BC: theta(1), WC: theta(1), TC: theta(1)


void Set::delete_list(Set::node_t* head){
  if(head == NULL){
    return ;
  }
  delete_list(head->next);
  delete head;
}


Set::~Set() {
  delete_list(this->head); 
}///BC: theta(size of set), WC: theta(size of set), TC: theta(size of set)


SetIterator Set::iterator() const {
	return SetIterator(*this);
}///BC: theta(1), WC: theta(1), TC: theta(1)


void Set::filter(Condition cond){
  node_t* new_head = NULL; 

  node_t* current = this->head;

  while(current != NULL){
    node_t* tmp = current->next;
    if(cond(current->elem)){
      if(new_head == NULL){
        new_head = current;
        new_head->next = NULL;
      }else{
        current->next = new_head;
        new_head = current;
      }
    }else{
      delete current;
    }
    current = tmp;
  }
  this->head = new_head;
}///BC: theta(size of set), WC: theta(size of set), TC: theta(size of set)
