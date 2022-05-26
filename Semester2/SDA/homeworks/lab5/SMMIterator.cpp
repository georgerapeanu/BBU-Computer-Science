#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
  this->dfs_stack = std::vector<SortedMultiMap::node_t*>();
  this->current_index = 0;
  if(map.root != NULL){
    
    this->dfs_stack.push_back(map.root);
    
    SortedMultiMap::node_t* tmp = this->dfs_stack.back();
  
    tmp = tmp->left;
    while(tmp != NULL){
      this->dfs_stack.push_back(tmp);
      tmp = tmp->left;
    }
  }
} // BC: theta(log(size)), WC: theta(log(size)), TC: theta(log(size))

void SMMIterator::first(){
    this->dfs_stack = std::vector<SortedMultiMap::node_t*>();
    this->current_index = 0;
    if(map.root != NULL){

        this->dfs_stack.push_back(map.root);

        SortedMultiMap::node_t* tmp = this->dfs_stack.back();

        tmp = tmp->left;
        while(tmp != NULL){
            this->dfs_stack.push_back(tmp);
            tmp = tmp->left;
        }
    }
} // BC: theta(log(size)), WC: theta(log(size)), TC: theta(log(size))

void SMMIterator::next(){
  if(this->valid() == false){
    throw std::exception();
  }
  current_index++;
  if(current_index >= this->dfs_stack.back()->size){
    current_index = 0;
    SortedMultiMap::node_t* last_node = this->dfs_stack.back();
    if(last_node->right != NULL){
        this->dfs_stack.push_back(last_node->right);
        while(this->dfs_stack.back()->left != NULL){
            this->dfs_stack.push_back(this->dfs_stack.back()->left);
        }
    }else{
        this->dfs_stack.pop_back();
        while(this->dfs_stack.empty() == false && this->dfs_stack.back()->right == last_node){
            last_node = this->dfs_stack.back();
            this->dfs_stack.pop_back();
        }
    }
  }
} //BC: theta(1), WC: theta(log(size)), TC: O(log(size))

bool SMMIterator::valid() const{
	return this->dfs_stack.empty() != true;
} // BC: theta(1), WC: theta(1), TC: theta(1);

TElem SMMIterator::getCurrent() const{
  if(this->valid() == false){
    throw std::exception();
  }
	return std::make_pair(this->dfs_stack.back()->key, this->dfs_stack.back()->values[current_index]);
} // BC: theta(1), WC: theta(1), TC: theta(1);


