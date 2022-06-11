#include <bits/stdc++.h>

using namespace std;

template <class T>
class Adder{
  vector<T> values;
  T __sum;
public:

  Adder(T value);

  Adder& operator + (const T value);

  Adder& operator ++ ();

  Adder& operator --();

  T sum();
};

template <class T>
Adder<T>::Adder(T value){
  values = {value};
  __sum = value;
}

template <class T>
Adder<T>& Adder<T>::operator + (const T value){
   this->values.push_back(value);
  __sum += value;
  return *this;
}
  
template <class T>
Adder<T>& Adder<T>::operator++(){
  __sum += this->values.back();
  this->values.push_back(this->values.back());
  return *this;
}

template <class T>
Adder<T>& Adder<T>::operator--(){
  if(this->values.empty()){
    throw runtime_error("No more values!");
  }
  __sum -= this->values.back();
  this->values.pop_back();
  return *this;
}

template<class T>
T Adder<T>::sum(){
  return __sum;
}

void function2(){
  Adder<int> add{5};
  add = add + 5 + 2;
  ++add;
  add + 8;
  cout << add.sum() << "\n";
  --add;
  cout << add.sum() << "\n";
  --(--add);
  cout << add.sum() << "\n";
  try{
    --(--(--add));
  }catch(runtime_error& ex){
    cout << ex.what();
  }
}

int main(){
  function2();
  return 0;
}
