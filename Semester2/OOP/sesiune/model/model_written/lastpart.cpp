#include <bits/stdc++.h>

class Beverage{
  std::string description;

public:
  
  Beverage(std::string description);
  ~Beverage();

  virtual double price() = 0;
  virtual void print();
};

Beverage::Beverage(std::string description):description(description){
  ;
}

Beverage::~Beverage(){
  ;
}

void Beverage::print(){
  std::cout << description + "\n";
}

class Coffee:public Beverage{
  public:
  Coffee();
  ~Coffee();
  virtual double price()override;
};

Coffee::Coffee():Beverage("Coffee"){
  ;
}

Coffee::~Coffee(){
  ;
}

double Coffee::price(){
  return 4.5;
}

class Tea:public Beverage{
  public:
  Tea();
  ~Tea();
  virtual double price()override;
};

Tea::Tea():Beverage("Tea"){
  ;
}

Tea::~Tea(){
  ;
}

double Tea::price(){
  return 3.5;
}

class BeverageWithMilk:public Beverage{
  Beverage* bev;
  int milkCount;

public:
  
  BeverageWithMilk(Beverage* bev, int milkCount);
  ~BeverageWithMilk();
  
  virtual void print()override;
  virtual double price()override;
};

BeverageWithMilk::BeverageWithMilk(Beverage* bev, int milkCount) : bev(bev), milkCount(milkCount), Beverage(""){
  ;
}

BeverageWithMilk::~BeverageWithMilk(){
  delete this->bev;
}

void BeverageWithMilk::print(){
  this->bev->print();
  std::cout << " " << this->milkCount << "\n";
}

double BeverageWithMilk::price(){
  return 0.5 * milkCount + this->bev->price();
}

class BeverageMachine{
  public:
  void prepare(std::string beverageType, int milkCount){
    Beverage* bev = NULL;

    if(beverageType == "Tea"){
      bev = new Tea();
    }else{
      bev = new Coffee();
    }

    BeverageWithMilk realBev(bev, milkCount);

    realBev.print();
    std::cout << realBev.price() << "\n";
  }
};

int main(){
  BeverageMachine machine;
  machine.prepare("Tea", 0);
  machine.prepare("Coffee", 1);
  machine.prepare("Coffee", 2);
}



