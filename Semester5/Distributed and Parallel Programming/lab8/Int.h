#ifndef INT_H
#define INT_H

#include <atomic>
#include <vector>

#include "Communicator.h"

class DSM;

class Int {
  int value;
  Communicator& communicator;
  int owner;
  std::string name;
  std::vector<int> subscribers;

public: 
  Int(Communicator& communicator, const std::string& name, int owner);
  ~Int();
  Int(const Int&) = delete;
  Int& operator = (const Int& other) = delete;
  Int(Int&& other) = default;
  
  int getValue()const;
  void setValue(int value);
  void compareAndExchange(int old_value, int new_value);
  const std::vector<int>& getSubscribers() const;

  friend class Communicator;
  friend class DSM;
};

#endif
