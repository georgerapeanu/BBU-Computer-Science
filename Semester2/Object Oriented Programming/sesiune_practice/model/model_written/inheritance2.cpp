#include <bits/stdc++.h>

class Person
{
public:
    Person() {
        std::cout << "Person{}";
    }
    virtual void print() = 0;
    virtual ~Person() {
        std::cout <<
                  "~Person()";
    }
};
class Student : public Person
{
public:
    Student() {
        std::cout << "Student{}";
    }
    void print() override {
        std::cout <<
                  "Student";
    }
    virtual ~Student() {
        std::cout <<
                  "~Student()";
    }
};

int main()
{
//    Person* p = new Person{}; //error
//    delete p;
    Person* s = new Student{}; // Person{}Student{}
    s->print();   //Student
    delete s; //~Student{}~Person{}
    return 0;
}
