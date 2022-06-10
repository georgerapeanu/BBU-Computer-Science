#include <bits/stdc++.h>

class B
{
public:
    B() {
        std::cout << "B{}";
    }
    virtual void print() {
        std::cout <<
                  "B";
    }
    virtual ~B() {
        std::cout << "~B()";
    }
};
class D : public B
{
public:
    D() {
        std::cout << "D{}";
    }
    void print() override {
        std::cout <<
                  "D";
    }
    virtual ~D() {
        std::cout << "~D()";
    }
};

int main()
{
    B* b[] = { new B{}, new D{} };
    b[0]->print();
    b[1]->print();
    delete b[0];
    delete b[1];
    return 0;
}
