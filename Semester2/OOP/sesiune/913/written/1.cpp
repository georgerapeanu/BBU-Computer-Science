#include <bits/stdc++.h>

class Complex{
  int a, b;

public:

  Complex(int a = 0,int b = 0) : a(a), b(b){
    ;
  }

  Complex(const Complex &other){
    this->a = other.a;
    this->b = other.b;
  }


  int getReal()const{
    return a;
  }

  int getImaginary()const{
    return b;
  }

  bool operator == (const Complex& other) const {
    return this->a == other.a && this->b == other.b;
  }

  Complex operator / (const int &other) const {
    if(other == 0){
      throw std::runtime_error("Division by zero!");
    }
    return Complex(this->a / other, this->b / other);
  }

  friend std::ostream& operator << (std::ostream& stream, const Complex& elem){
    stream << elem.getReal() << "+" << elem.getImaginary() << "i";
    return stream;
  }
};

template<class T>
class Vector{
  std::vector<T> elems;
  public:
  
  Vector(const std::vector<T> &elems):elems(elems){
    ;
  }

  void printAll(std::ostream& stream){
    for(auto it:elems){
      stream << it << ",";
    }
    stream << "\n";
  }
};

void testComplex(){
  Complex a{}, b{ 1, 2 }, c{ 6, 4 }, d{ b }; /// (int a = 0, int b = 0), copy constructor
  assert(a.getReal() == 0 && a.getImaginary() == 0); ///getters for real and imaginary
  assert(c.getImaginary() == 4);
  assert(b == d); // == operator

  Complex res1 = c / 2; // / operator
  std::cout << res1 << "\n"; //ostream

  try{
    Complex res2 = b / 0;
  }catch(std::runtime_error& e){
    assert(strcmp(e.what(), "Division by zero!") == 0); //throws runtime_error for 0
  }

  Vector<std::string> v1{ std::vector<std::string>{"hello", "bye"} } ; //constructor with std::vector
  v1.printAll(std::cout); //printall with ostream
  Vector<Complex> v2{ std::vector<Complex> {a, b, c, d} };
  v2.printAll(std::cout);
}

int main(){
  testComplex();
  return 0;
}
