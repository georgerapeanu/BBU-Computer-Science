#pragma once
#include <iterator>

template <typename T>
class DynamicVector {
private:
    T* elems;
    int size;
    int capacity;
public:
    DynamicVector(int capacity = 10);
    DynamicVector(const DynamicVector& v);
    ~DynamicVector();

    DynamicVector& operator=(const DynamicVector& v);

    void add(const T& elem);
    int getSize() const;

    T& operator [] (const int pos);
private:
    void resize();

public:
    class iterator {
    private:
        T* pointer;
    public:
        iterator(T* pointer);
        T& operator * ();
        bool operator != (const iterator &other)const;
        iterator& operator ++(int a);
        iterator& operator ++();
    };
    DynamicVector<T>::iterator begin() const;
    DynamicVector<T>::iterator end() const;
};

template<typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
    this->elems = new T[capacity];
    this->capacity = capacity;
    this->size = 0;
}

template<typename T>
DynamicVector<T>::DynamicVector(const DynamicVector& v){
  this->elems = new T[v.capacity];
  this->capacity = v.capacity;
  this->size = v.size;

  for(int i = 0;i < v.capacity;i++){
    this->elems[i] = v.elems[i];
  }
}

template<typename T>
DynamicVector<T>::~DynamicVector()
{
    delete []this->elems;
}

template<typename T>
void DynamicVector<T>::add(const T& elem)
{
    if (this->size == this->capacity)
    {
        this->resize();
    }
    this->elems[this->size++] = elem;
}

template<typename T>
int DynamicVector<T>::getSize() const
{
    return this->size;
}

template<typename T>
void DynamicVector<T>::resize()
{
    this->capacity *= 2;

    T* elems = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
    {
        elems[i] = this->elems[i];
    }

    delete []this->elems;
    this->elems = elems;
}
    
template<typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector& v){
  this->size = v.size;
  this->capacity = v.capacity;
  delete[] this->elems;
  this->elems = new T[v.capacity];

  for(int i = 0;i < v.capacity;i++){
    this->elems[i] = v.elems[i];
  }
  return *this;
}

template<typename T>
DynamicVector<T>::iterator::iterator(T *p) {
  pointer = p;
}

template<typename T>
T &DynamicVector<T>::iterator::operator*() {
    return *pointer;
}

template<typename T>
bool DynamicVector<T>::iterator::operator!=(const DynamicVector::iterator &other) const {
    return this->pointer != other.pointer;
}

template<typename T>
typename DynamicVector<T>::iterator& DynamicVector<T>::iterator::operator++(int a) {
    this->pointer++;
    return *this;
}

template<typename T>
typename DynamicVector<T>::iterator& DynamicVector<T>::iterator::operator++() {
    iterator it(this->pointer);
    this->pointer++;
    return it;
}

template<typename T>
typename DynamicVector<T>::iterator DynamicVector<T>::begin() const {
  iterator it(elems);
  return it; 
}

template<typename T>
typename DynamicVector<T>::iterator DynamicVector<T>::end() const {
  iterator it(elems + size);
  return it; 
}

template<typename T>
T& DynamicVector<T>::operator[](const int pos){
    return this->elems[pos];
}

