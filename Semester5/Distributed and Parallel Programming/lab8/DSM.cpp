#include <string>
#include <map>

#include "DSM.h"

using namespace std;

DSM::DSM(): table(), communicator(), table_mutex() {
  communicator_thread = thread([this]() {
    while(communicator.recv()) {

    }
  });
}

#include <iostream>
DSM::~DSM() {
  cerr << "DSM desturctor called" << endl;
  table.clear();
  communicator.~Communicator();
  communicator_thread.join();
  cerr << "DSM desturctor finished" << endl;
}

bool DSM::exists(const std::string& name, int owner) {
  return table.count({name, owner});
}
Int& DSM::getInt(const std::string& name, int owner) {
  lock_guard<mutex> guard(table_mutex);
  if(!table.count(make_pair(name, owner))) {
    table.insert(make_pair(make_pair(name, owner), make_shared<Int>(communicator, name, owner)));
  }
  return *table.at({name, owner});
}

DSM& DSM::getInstance() {
  static DSM dsm;
  return dsm;
}

int DSM::get_me() const {
  return communicator.get_me();
}
