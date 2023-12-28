#include "Communicator.h"
#include "DSM.h"
#include "Int.h"

#include <mutex>
#include <string>
#include <mpi.h>
#include <assert.h>

using namespace std;

void Communicator::send_update(const std::string& name, Int& a, int value) {
  cerr << "entering send update from process " << me << " " << name << " " << value << endl;
  lock_guard<mutex> guard(this->send_mutex);
  a.value = value;

  for(auto it: a.getSubscribers()) {
    int length = (int)name.size();
    MPI_Request req;
    MPI_Isend(&length, 1, MPI_INT, it, 1, MPI_COMM_WORLD, &req);
    MPI_Request_free(&req);
    MPI_Isend(name.c_str(), length, MPI_CHAR, it, 1, MPI_COMM_WORLD, &req);   
    MPI_Request_free(&req);
    int tmp = a.getValue();
    MPI_Isend(&tmp, 1, MPI_INT, it, 1, MPI_COMM_WORLD, &req);   
    MPI_Request_free(&req);
  }
}

void Communicator::send_compare_and_swap(const std::string& name, Int& a, int old_value, int new_value){
  cerr << "entering send cas from process " << me << " " << name << " " << old_value << " " << new_value << endl;
  lock_guard<mutex> guard(this->send_mutex);
  if(a.value == old_value) {
    a.value = new_value;
    for(auto it: a.getSubscribers()) {
      int length = (int)name.size();
      MPI_Request req;
      MPI_Isend(&length, 1, MPI_INT, it, 1, MPI_COMM_WORLD, &req);   
      MPI_Request_free(&req);
      MPI_Isend(name.c_str(), length, MPI_CHAR, it, 1, MPI_COMM_WORLD, &req);   
      MPI_Request_free(&req);
      int tmp = a.getValue();
      MPI_Isend(&tmp, 1, MPI_INT, it, 1, MPI_COMM_WORLD, &req);   
      MPI_Request_free(&req);
    }
  }
}

void Communicator::request_update(const std::string& name, int owner, int value) {
  cerr << "entering request update from process " << me << " " << owner << " " << value << endl;
  lock_guard<mutex> guard(this->send_mutex);
  assert(owner != me);
  int length = (int)name.size();
  MPI_Request req;
  MPI_Isend(&length, 1, MPI_INT, owner, 2, MPI_COMM_WORLD, &req);   
  MPI_Request_free(&req);
  MPI_Isend(name.c_str(), length, MPI_CHAR, owner, 2, MPI_COMM_WORLD, &req);   
  MPI_Request_free(&req);
  int tmp = value;
  MPI_Isend(&tmp, 1, MPI_INT, owner, 2, MPI_COMM_WORLD, &req);   
  MPI_Request_free(&req);
}
  
void Communicator::request_compare_and_exchange(const std::string& name, int owner, int old_value, int new_value) {
  cerr << "entering request cas from process " << me << " " << name << " " << owner << " " << old_value << " " << new_value << endl;
  lock_guard<mutex> guard(this->send_mutex);
  assert(owner != me);
  int length = (int)name.size();
  MPI_Request req;
  MPI_Isend(&length, 1, MPI_INT, owner, 3, MPI_COMM_WORLD, &req);   
  MPI_Request_free(&req);
  MPI_Isend(name.c_str(), length, MPI_CHAR, owner, 3, MPI_COMM_WORLD, &req);   
  MPI_Request_free(&req);
  int tmp = old_value;
  MPI_Isend(&tmp, 1, MPI_INT, owner, 3, MPI_COMM_WORLD, &req);   
  MPI_Request_free(&req);
 
  tmp = new_value;
  MPI_Isend(&tmp, 1, MPI_INT, owner, 3, MPI_COMM_WORLD, &req);   
  MPI_Request_free(&req);
}

void Communicator::send_subscribe(const std::string& name, int owner) {
  cerr << "entering send subscribe from process " << me << " " << name << " " << owner << endl;
  lock_guard<mutex> guard(this->send_mutex);
  assert(owner != me);
  int length = (int)name.size();
  MPI_Request req;
  MPI_Isend(&length, 1, MPI_INT, owner, 4, MPI_COMM_WORLD, &req);   
  MPI_Request_free(&req);
  MPI_Isend(name.c_str(), length, MPI_CHAR, owner, 4, MPI_COMM_WORLD, &req);   
  MPI_Request_free(&req);
}

void Communicator::send_unsubscribe(const std::string& name, int owner) {
  cerr << "entering send unsubscribe from process " << me << " " << name << " " << owner << endl;
  lock_guard<mutex> guard(this->send_mutex);
  assert(owner != me);
  int length = (int)name.size();
  MPI_Request req;
  MPI_Isend(&length, 1, MPI_INT, owner, 5, MPI_COMM_WORLD, &req);   
  MPI_Request_free(&req);
  MPI_Isend(name.c_str(), length, MPI_CHAR, owner, 5, MPI_COMM_WORLD, &req);   
  MPI_Request_free(&req);
}

bool Communicator::recv() {
  MPI_Status status;
  MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
  cerr << "Process " << me << " " << status.MPI_SOURCE << " " << status.MPI_TAG << endl;
  switch(status.MPI_TAG) {
    case 1: {
      int length;
      MPI_Recv(&length, 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      string name((size_t)length, ' ');
      MPI_Recv(name.data(), length, MPI_CHAR, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      int value;
      MPI_Recv(&value, 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      if(DSM::getInstance().exists(name, status.MPI_SOURCE)) {
        DSM::getInstance().getInt(name, status.MPI_SOURCE).value = value;//if doesnt exist ignore
      }
      break;
    }
    case 2: {
      int length;
      MPI_Recv(&length, 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      string name((size_t)length, ' ');
      MPI_Recv(name.data(), length, MPI_CHAR, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      int value;
      MPI_Recv(&value, 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      DSM::getInstance().getInt(name, me).setValue(value);
      break;
    }
    case 3: {
      int length;
      MPI_Recv(&length, 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      string name((size_t)length, ' ');
      MPI_Recv(name.data(), length, MPI_CHAR, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      int old_value;
      MPI_Recv(&old_value, 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      int new_value;
      MPI_Recv(&new_value, 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      DSM::getInstance().getInt(name, me).compareAndExchange(old_value, new_value);
      break;
    }
    case 4: {
      int length;
      MPI_Recv(&length, 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      string name((size_t)length, ' ');
      MPI_Recv(name.data(), length, MPI_CHAR, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      Int& a(DSM::getInstance().getInt(name, me));
      a.subscribers.push_back(status.MPI_SOURCE);
      send_update(name, a, a.getValue());
      break;
    }
    case 5: {
      int length;
      MPI_Recv(&length, 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      string name((size_t)length, ' ');
      MPI_Recv(name.data(), length, MPI_CHAR, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      Int& a(DSM::getInstance().getInt(name, me));
      a.subscribers.erase(find(a.subscribers.begin(), a.subscribers.end(), status.MPI_SOURCE));
      break;
    }
    default: {
      return false;
    }
  }
  return true;
}

Communicator::Communicator() {
  MPI_Init(0, 0);
  MPI_Comm_rank(MPI_COMM_WORLD, &me);
}

Communicator::~Communicator() {
  MPI_Request req;
  int tmp = 6;
  MPI_Isend(&tmp, 1, MPI_INT, me, 6, MPI_COMM_WORLD, &req);   
  MPI_Request_free(&req);
  MPI_Finalize();
}

int Communicator::get_me() const {
  return me;
}
