#ifndef DSM_H
#define DSM_H

#include <string>
#include <map>
#include <thread>

#include "Int.h"
#include "Communicator.h"
#include <memory>

class DSM {
  std::map<std::pair<std::string, int>, std::shared_ptr<Int>> table;
  Communicator communicator;
  std::mutex table_mutex;
  std::thread communicator_thread;
  DSM();
public: 
  ~DSM();
  Int& getInt(const std::string& name, int owner);
  bool exists(const std::string& name, int owner);
  static DSM& getInstance();
  int get_me() const ;
};

#endif
