#include <bits/stdc++.h>

using namespace std;

class B
{
public:
  void f() { cout << "B.f "; }
  virtual ~B() {}
};

class D1 : public B
{
public:
  virtual void f(){ cout << "D1.f "; }
  virtual ~D1() {}
};

class D2 : public D1
{
public:
  void f() { cout << "D2.f ";}
};

int main(){
  B* b1 = new B{}; b1->f(); delete b1; // B.f 
  B* b2 = new D1{}; b2->f(); delete b2; // B.f
  B* b3 = new D2{}; b3->f(); delete b3;  // B.f
  D2* d = new D2{}; d->f(); delete d;// D2.f

}

