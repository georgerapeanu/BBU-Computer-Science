#include <bits/stdc++.h>

class Ex1 {
  public:
  Ex1() {std::cout << "Exception1 ";};
  Ex1(const Ex1& ex) {std::cout << "Copy_ex1 "; }
};

class Ex2: public Ex1{
public:
  Ex2(){ std::cout << "Exception2 "; }
  Ex2(const Ex2& ex){ std::cout << "Copy_ex2"; }
};

void except(int x) {
  if( x < 0 ){
    throw Ex1{};
  } else if (x == 0){
    throw Ex2{};
  }
  std::cout << "Done ";
}

int main(){
  try {
    std::cout << "Start "; 
    try{
      except(0);
    }
    catch(Ex1& e) {}
    except(-2);
  } catch(Ex1 e) {}
  return 0;
}

//Start Exception1 Exception2 Exception1 Copy_ex1
