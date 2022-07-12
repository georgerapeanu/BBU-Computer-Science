#include <bits/stdc++.h>

int main(){
  std::vector<int> v{1,2,3,4,5};
  std::vector<int>::iterator it = std::find(v.begin(), v.end(), 4);
  v.insert(it, 8); ///1,2,3,8 ,4,5
  it = v.begin() + 2;
  *it = 10; //1,2,10,8, 4,5
  std::vector<int> x;
  std::copy_if(v.begin(), v.end(), back_inserter(x), [](int a){ return a % 2 == 0;}); //2, 10, 8, 4
  for(auto a:x){
    std::cout << a << " ";
  }

  return 0;
}
