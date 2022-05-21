#pragma once
#include "SortedMultiMap.h"
#include <vector>


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

  std::vector<SortedMultiMap::node_t*> node_stack;
  SortedMultiMap::node_t* current_node;
  int current_index;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

