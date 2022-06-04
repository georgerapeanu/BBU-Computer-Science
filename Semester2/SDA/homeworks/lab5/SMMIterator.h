#pragma once
#include "SortedMultiMap.h"



class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

    void stack_push_back(SortedMultiMap::node_t* current);
    void stack_pop_back();
    SortedMultiMap::node_t* stack_back()const;

  SortedMultiMap::node_t** dfs_stack;
  int stack_size;
  int stack_capacity;
  int current_index;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

