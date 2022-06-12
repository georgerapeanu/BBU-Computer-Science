#include <bits/stdc++.h>
#include <iostream>

class Activity{
  std::string description;
  std::string when;

  public:

  Activity(std::string description, std::string when){
    this->description = description;
    this->when = when;
  }

  friend std::ostream& operator << (std::ostream& os, const Activity &activity){
    os << "Activity " << activity.description << " will take place at " << activity.when << ".";
    return os;
  }
};

template <class T>
class ToDo{
  std::vector<T> elems;

public:

  ToDo& operator += (const T& elem){
    elems.push_back(elem);
    return *this;
  }

  typename std::vector<T>::iterator begin(){
    return elems.begin();
  }

  typename std::vector<T>::iterator end(){
    return elems.end();
  }

  void reversePrint(std::ostream& os){
    for(int i = (int)elems.size() - 1;i >= 0;i--){
      std::cout << elems[i] << "\n";
    }
  }
};

void ToDoList(){
  ToDo<Activity> todo{};
  Activity tiff{ "go to TIFF movie", "20:00"};
  todo += tiff;
  Activity project{ "present project assignment" , "09.20"};
  todo += project;

  for(auto a:todo){
    std::cout << a << "\n";
  }

  todo.reversePrint(std::cout);
}

int main(){
  ToDoList();
  return 0;
}
