#include <bits/stdc++.h>

using namespace std;

int fct(string v) {
  if(v == "") { throw string{ "2" }; }
  cout << "1 ";
  if(v.size() > 4) { throw runtime_error("Not empty"); }
  return 0;
}

int main() {
  try{
    cout << fct("Hi") << " "; ///1 0 
    cout << fct("Hello") << " "; //1 throw
    cout << fct("") << " ";
  }catch( string& ex ) {
    cout << ex; //not caught
  } catch (runtime_error& e){
    cout << e.what(); //Not empty
  }

  //1 0 1 Not empty
  return 0;
}
