#include <atomic>
#include <vector>
#include "Communicator.h"
#include "Int.h"

using namespace std;

Int::Int(Communicator& communicator, const std::string& name, int owner): value(0), communicator(communicator), owner(owner), name(name), subscribers(){
  if(owner != communicator.get_me()) {
    communicator.send_subscribe(name, owner);
  }
};

#include <iostream>
Int::~Int() {
  cerr << "int " << name << " " << owner << " " << communicator.get_me() << endl;
  if(owner != communicator.get_me()) {
    communicator.send_unsubscribe(name, owner);
  }
}
int Int::getValue() const {
  return value;
}

void Int::setValue(int value) {
  communicator.send_update(name, *this, value);
}
void Int::compareAndExchange(int old_value, int new_value) {
  communicator.send_compare_and_swap(name, *this, old_value, new_value);
}
const std::vector<int>& Int::getSubscribers() const {
  return subscribers;
}


