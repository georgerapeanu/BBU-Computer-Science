
#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
  this->node_stack = std::vector<SortedMultiMap::node_t*>();
  this->current_node = NULL;
  this->current_index = 0;
  if(map.root != NULL){
    
    this->node_stack.push_back(map.root);
    
    SortedMultiMap::node_t* tmp = this->node_stack.back();
  
    tmp = tmp->left;
    while(tmp != NULL){
      this->node_stack.push_back(tmp);
      tmp = tmp->left;
    }
    current_node = this->node_stack.back();
    this->node_stack.pop_back();
    tmp = current_node->right;
    while(tmp != NULL){
      this->node_stack.push_back(tmp);
      tmp = tmp->left;
    }
  }
} // BC: theta(log(size)), WC: theta(log(size)), TC: theta(log(size))

void SMMIterator::first(){
  this->node_stack = std::vector<SortedMultiMap::node_t*>();
  this->current_node = NULL;
  this->current_index = 0;
  this->node_stack.push_back(map.root);
  if(map.root == NULL){
      return ;
  }
  
  SortedMultiMap::node_t* tmp = this->node_stack.back();

  tmp = tmp->left;
  while(tmp != NULL){
    this->node_stack.push_back(tmp);
    tmp = tmp->left;
  }
  current_node = this->node_stack.back();
  this->node_stack.pop_back();
  tmp = current_node->right;
  while(tmp != NULL){
    this->node_stack.push_back(tmp);
    tmp = tmp->left;
  }
} // BC: theta(log(size)), WC: theta(log(size)), TC: theta(log(size))

void SMMIterator::next(){
  if(this->valid() == false){
    throw std::exception();
  }
  current_index++;
  if(current_index >= this->current_node->size){
    current_index = 0;
    current_node = NULL;
    if(this->node_stack.empty()){
      return ;
    }
    current_node = this->node_stack.back();
    this->node_stack.pop_back();
    SortedMultiMap::node_t* tmp = current_node->right;
    while(tmp != NULL){
      this->node_stack.push_back(tmp);
      tmp = tmp->left;
    }
  }
} //BC: theta(1), WC: theta(log(size)), TC: O(log(size))

bool SMMIterator::valid() const{
	return current_node != NULL;
} // BC: theta(1), WC: theta(1), TC: theta(1);

TElem SMMIterator::getCurrent() const{
  if(this->valid() == false){
    throw std::exception();
  }
	return std::make_pair(this->current_node->key, this->current_node->values[current_index]);
} // BC: theta(1), WC: theta(1), TC: theta(1);


