#include <bits/stdc++.h>
#include <mpi.h>
#include "DSM.h"

using namespace std;

int main() {
  DSM& dsm(DSM::getInstance());

  if(dsm.get_me() == 0) {
    cerr << "process 0 gets hold of process 1 'a'" << endl;
    Int& a(dsm.getInt("a", 1));
    usleep(5000000);
    cerr << "process 0 value of a is now " << a.getValue() << endl;
    cerr << "process 0 define value b" << endl;
    Int& b(dsm.getInt("b", 0));
    b.setValue(3);
    usleep(5000000);
  } else {
    usleep(2500000);
    cerr << "process 1 sets 'a' to 2" << endl;
    Int& a(dsm.getInt("a", 1));
    a.setValue(2);
    usleep(5000000);
    Int& b(dsm.getInt("b", 0));
    usleep(5000000);
    cerr << "process 1 value of b from process 0 is " << b.getValue() << endl;
    b.compareAndExchange(3, 1);
    cerr << "Process 1 requested cas 3 1 of process 0 b" << endl;
    usleep(5000000);
    cerr << "Process 1 value of process 0 b is " << b.getValue() << endl;
  }
 
  usleep(5000000); // allow processes to end;
  return 0;
}
