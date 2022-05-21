#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


class SortedMultiMap {
	friend class SMMIterator;
    private:

    Relation r;
    struct node_t{
      TKey key;
      TValue* values;
      int size;
      int capacity;
      int height;

      node_t* left;
      node_t* right;
    } *root;
    int __size;

    // recalculate the height of a node
    void update_height(node_t* root);

    // gets the height of a node
    int get_height(node_t* root);

    // rotate node to the left
    node_t* rotate_left(node_t* root);

    // rotate node to the right
    node_t* rotate_right(node_t* root);

    // rotate the node in order to be balanced
    node_t* fix(node_t* root);

    // for creating a new node
    node_t* create_node(TKey key, node_t* left, node_t* right);
    
    // for adding a value to a node
    void add_to_node(node_t* node, TValue value);

    // remove value from a node
    void remove_from_node(node_t* node, TValue value);
    
    // add to the tree recursively
    node_t* recursive_add(node_t* root, TKey key, TValue value);
    
    // add to the tree recursively
    node_t* recursive_remove(node_t* root, TKey key, TValue value);

    // recursively frees the used memory
    void recursive_delete(node_t* root);

    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
