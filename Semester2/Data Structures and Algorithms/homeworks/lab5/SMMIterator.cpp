#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
  this->dfs_stack = new SortedMultiMap::node_t*[1];
  this->stack_capacity = 1;
  this->stack_size = 0;
  this->current_index = 0;
  if(map.root != NULL){
    
    stack_push_back(map.root);
    
    SortedMultiMap::node_t* tmp = stack_back();
  
    tmp = tmp->left;
    while(tmp != NULL){
      stack_push_back(tmp);
      tmp = tmp->left;
    }
  }
} // BC: theta(log(size)), WC: theta(log(size)), TC: theta(log(size))

void SMMIterator::first(){
    delete[] this->dfs_stack;
    this->dfs_stack = new SortedMultiMap::node_t*[1];
    this->stack_capacity = 1;
    this->stack_size = 0;
    this->current_index = 0;
    if(map.root != NULL){

        stack_push_back(map.root);

        SortedMultiMap::node_t* tmp = stack_back();

        tmp = tmp->left;
        while(tmp != NULL){
            stack_push_back(tmp);
            tmp = tmp->left;
        }
    }
} // BC: theta(log(size)), WC: theta(log(size)), TC: theta(log(size))

void SMMIterator::next(){
  if(this->valid() == false){
    throw std::exception();
  }
  current_index++;
  if(current_index >= stack_back()->size){
    current_index = 0;
    SortedMultiMap::node_t* last_node = stack_back();
    if(last_node->right != NULL){
        stack_push_back(last_node->right);
        while(stack_back()->left != NULL){
            stack_push_back(stack_back()->left);
        }
    }else{
        stack_pop_back();
        while(this->stack_size > 0 && stack_back()->right == last_node){
            last_node = stack_back();
            stack_pop_back();
        }
    }
  }
} //BC: theta(1), WC: theta(log(size)), TC: O(log(size))

bool SMMIterator::valid() const{
	return stack_size > 0;
} // BC: theta(1), WC: theta(1), TC: theta(1);

TElem SMMIterator::getCurrent() const{
  if(this->valid() == false){
    throw std::exception();
  }
	return std::make_pair(stack_back()->key, stack_back()->values[current_index]);
}// BC: theta(1), WC: theta(1), TC: theta(1);

void SMMIterator::stack_push_back(SortedMultiMap::node_t *current) {
    if(this->stack_capacity == this->stack_size){
        SortedMultiMap::node_t** new_elems = new SortedMultiMap::node_t*[this->stack_capacity * 2];
        for(int i = 0;i < this->stack_capacity;i++){
            new_elems[i] = this->dfs_stack[i];
        }
        delete[] this->dfs_stack;
        this->dfs_stack = new_elems;
        this->stack_capacity *= 2;
    }
    this->dfs_stack[this->stack_size++] = current;
}// BC: theta(1), WC: theta(size), TC: O(size)

void SMMIterator::stack_pop_back() {
    this->stack_size--;
}// BC: theta(1), WC: theta(1), TC: theta(1)

SortedMultiMap::node_t* SMMIterator::stack_back() const {
    return this->dfs_stack[this->stack_size - 1];
}// BC: theta(1), WC: theta(1), TC: theta(1)





