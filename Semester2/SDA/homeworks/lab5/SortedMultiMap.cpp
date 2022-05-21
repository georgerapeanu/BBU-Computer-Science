
#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::node_t* SortedMultiMap::create_node(TKey key, node_t* left = NULL, node_t* right = NULL) {
  node_t* ans = new node_t();
  ans->values = new TValue[1];
  ans->capacity = 1;
  ans->size = 0;
  ans->left = left;
  ans->right = right;
  ans->key = key;
  ans->height = 1;
  return ans;
} // BC: theta(1), WC: theta(1), TC: theta(1)

int SortedMultiMap::get_height(node_t* root) {
  if(root == NULL){
    return 0;
  }
  return root->height;
} // BC: theta(1), WC: theta(1), TC: theta(1)

void SortedMultiMap::update_height(node_t* root) {
  root->height = 1 + max(get_height(root->left), get_height(root->right));  
} // BC: theta(1), WC: theta(1), TC: theta(1)

SortedMultiMap::node_t* SortedMultiMap::rotate_left(node_t* root) {
  node_t* new_root = root->right;
  root->right = new_root->left;
  new_root->left = root;
  update_height(root);
  update_height(new_root);
  return new_root;
} // BC: theta(1), WC: theta(1), TC: theta(1)

SortedMultiMap::node_t* SortedMultiMap::rotate_right(node_t* root) {
  node_t* new_root = root->left;
  root->left = new_root->right;
  new_root->right = root;
  update_height(root);
  update_height(new_root);
  return new_root;
} // BC: theta(1), WC: theta(1), TC: theta(1)

SortedMultiMap::node_t* SortedMultiMap::fix(node_t* root) {
  while(get_height(root->left) - get_height(root->right) > 1){
    root = rotate_right(root);
  }
  while(get_height(root->right) - get_height(root->left) > 1) {
    root = rotate_left(root);
  }
  return root;
} // BC: theta(1), WC: theta(number of nodes), TC: O(number of nodes)

void SortedMultiMap::add_to_node(node_t* node, TValue value){
  if(node->size == node->capacity){
    TValue* new_values = new TValue[2 * node->capacity];
    for(int i = 0;i < node->capacity;i++){
      new_values[i] = node->values[i];
    }
    delete[] node->values;
    node->values = new_values;
    node->capacity *= 2;
  }
  node->values[node->size++] = value;
} //BC: theta(1), WC: theta(size of array), TC: O(size of array)

void SortedMultiMap::remove_from_node(node_t* node, TValue value){
  int index = -1;
  for(int i = 0;i < node->size;i++){
    if(node->values[i] == value){
      index = i;
      break;
    }
  }
  if(index == -1){
    throw exception();
  }

  for(int i = index;i + 1 < node->size;i++){
    node->values[i] = node->values[i + 1];
  }
  node->size--;
} //BC: theta(size of array), WC: theta(size of array), TC: theta(size of array)


SortedMultiMap::SortedMultiMap(Relation r): r(r) {
  this->root = NULL;
  this->__size = 0;
}// BC: theta(1), WC: theta(1), TC: theta(1)

SortedMultiMap::node_t* SortedMultiMap::recursive_add(node_t* root, TKey key, TValue value){
  if(root == NULL){
    root = create_node(key);
    add_to_node(root, value);
    return root;
  }
  if(root->key == key){
    add_to_node(root, value);
    return root;
  }
  if(this->r(key, root->key)){
    root->left = recursive_add(root->left, key, value);
  }else{
    root->right = recursive_add(root->right, key, value);
  }
  update_height(root);
  root = fix(root);
  return root;
} //BC : theta(1), WC: theta(size), TC: O(size)


void SortedMultiMap::add(TKey c, TValue v) {
  this->root = recursive_add(this->root, c, v);  
  this->__size++;
} //BC : theta(1), WC: theta(size), TC: O(size)

vector<TValue> SortedMultiMap::search(TKey c) const {
	node_t* current = this->root;
  while(current != NULL && current->key != c){
    if(this->r(c, current->key)){
      current = current->left;
    }else{
      current = current->right;
    }
  }
  vector<TValue> ans;
  if(current != NULL){
    for(int i = 0;i < current->size;i++){
      ans.push_back(current->values[i]);
    }
  }
  return ans;
} //BC : theta(1), WC: theta(size), TC: O(size)

SortedMultiMap::node_t* SortedMultiMap::recursive_remove(node_t* root, TKey key, TValue value){
  if(root == NULL){
    throw exception();
  }
  if(root->key == key){
    remove_from_node(root, value);
    if(root->size == 0){
        node_t* previous_father = NULL;
        node_t* previous = NULL;
        node_t* current = root->left;
        while(current != NULL){
            previous_father = previous;
            previous = current;
            current = current->right;
        }
        if(previous == NULL){
            node_t* tmp = root->right;
            delete[] root->values;
            delete root;
            if(tmp != NULL){
                update_height(tmp);
            }
            return tmp;
        }
        previous->right = root->right;
        if(previous_father != NULL){
            previous_father->right = NULL;
        }
        delete[] root->values;
        delete root;
        if(previous != NULL){
            update_height(previous);
        }
        return previous;
    }
    return root;
  }
  if(this->r(key, root->key)){
    root->left = recursive_remove(root->left, key, value);
  }else{
    root->right = recursive_remove(root->right, key, value);
  }
  update_height(root);
  root = fix(root);
  return root;
} //BC : theta(1), WC: theta(size), TC: O(size)

bool SortedMultiMap::remove(TKey c, TValue v) {
  bool success = true;
  try{
    this->root = recursive_remove(this->root, c, v);
  } catch(exception &ex){
    success = false;
  }
  __size -= success;
  return success;
} //BC : theta(1), WC: theta(size), TC: O(size)


int SortedMultiMap::size() const {
	return __size;
} //BC : theta(1), WC: theta(1), TC: theta(1)

bool SortedMultiMap::isEmpty() const {
	return (__size == 0);
} //BC : theta(1), WC: theta(1), TC: theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
} //BC : theta(1), WC: theta(1), TC: theta(1)

void SortedMultiMap::recursive_delete(node_t* root){
  if(root == NULL){
    return ;
  }
  recursive_delete(root->left);
  recursive_delete(root->right);
  delete[] root->values;
  delete root;
} //BC : theta(size), WC: theta(size), TC: theta(size)

SortedMultiMap::~SortedMultiMap() {
  this->__size = 0;
  recursive_delete(this->root);
} //BC : theta(size), WC: theta(size), TC: theta(size)
