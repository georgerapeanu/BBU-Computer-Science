#pragma once
#include "IteratedList.h"

//DO NOT CHANGE THIS PART
class IteratedList;
typedef int TElem;

class ListIterator{
	friend class IteratedList;
private:
  int index;

	//DO NOT CHANGE THIS PART
	IteratedList& list;
	ListIterator(IteratedList& list);

public:
	void first();
	void next();
	bool valid() const;
  TElem getCurrent() const;

  TElem remove();
};


