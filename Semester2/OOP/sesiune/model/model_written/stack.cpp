#include <bits/stdc++.h>

template<class T>
class Stack{
  T* elems;
  int capacity;
  int top;

public:

  Stack(int capacity);

  ~Stack();
  
  Stack& operator + (const T &elem);

  T pop();

  int getMaxCapacity();
};
  
template <class T>
Stack<T>::Stack(int capacity){
  this->capacity = capacity;
  elems = new T[capacity];
  top = 0;
}

template<class T>
Stack<T>::~Stack(){
  delete[] elems;
}

template<class T>
Stack<T>& Stack<T>::operator + (const T &elem){
  if(this->top == this->capacity){
    throw std::runtime_error("Stack is full!");
  }
  elems[top++] = elem;
  return *this;
}

template<class T>
T Stack<T>::pop(){
  if(this->top == 0){
    throw std::runtime_error("Stack is empty!");
  }
  return elems[--top];
}
  
template<class T>
int Stack<T>::getMaxCapacity(){
  return capacity;
}

void testStack()
{
  Stack<std::string> s{ 2 };
  assert(s.getMaxCapacity() == 2);
  try {
    s = s + "examination";
    s = s + "oop";
    s = s + "test";
  } catch (std::exception &e) {
    assert(strcmp(e.what(), "Stack is full!") == 0);
  }

  assert(s.pop() == "oop");
  assert(s.pop() == "examination");
}

int main(){
  testStack();
  return 0;
}
