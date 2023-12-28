#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <mutex>
#include <string>

class Int;
class DSM;

class Communicator {
  int me;
  std::mutex send_mutex;
  void send_update(const std::string& name, Int& a, int value);
  void send_compare_and_swap(const std::string& name, Int& a, int old_value, int new_value);
  void request_update(const std::string& name, int owner, int value);
  void request_compare_and_exchange(const std::string& name, int owner, int old_value, int new_value);
  void send_subscribe(const std::string& name, int owner);
  void send_unsubscribe(const std::string& name, int owner);
  bool recv();
  int get_me() const ;

  Communicator();
  ~Communicator();

  friend class Int;
  friend class DSM;
};

#endif
