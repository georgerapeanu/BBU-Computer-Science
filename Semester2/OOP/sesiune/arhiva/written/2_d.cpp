#include <bits/stdc++.h>

using namespace std;

class A{
private:
  int* x;
public:

  A(int _x = 0) {
    x = new int{ _x };
  }

  A(const A& a){
    x = new int { *a.x };
  }

  int get() { return *x; }
  void set(int __x) {*x = __x;}

  ~A() { delete x; }
};

int main(){
  
  A a1, a2;a1.set(3); // 3, 0
  A a3;a3 = a1; /// 3, 0, 3
  A a4 = a1; /// 3, 0, 3, 3
  a1.set(5); // 5, 0, 5, 3

  cout << a1.get() << " ";
  cout << a2.get() << " ";
  cout << a3.get() << " ";
  cout << a4.get() << " ";

  cout.flush();
  //crash
  return 0;
}
