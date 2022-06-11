#include <bits/stdc++.h>

using namespace std;

class B {
public:
  B() {}
  B(const B& b) { cout << "copy ";  }
  virtual void f() { cout << "B.f "; }
  void g(B b) {cout << "B.g"; }
  virtual ~B() { cout << "~B"; }
};

class D: public B{
public:
  D() {};
  void f() {B::f(); cout << "D.f";}
  void g(D d){ B::g(d); cout << "D.g";}
};

int main(){
  B* b = new B{};
  D* d = new D{};
  d->f(); // B.f D.f
//  d->g(*b); // error
  delete b; // ~B
  delete d; // ~B

  return 0;
}
