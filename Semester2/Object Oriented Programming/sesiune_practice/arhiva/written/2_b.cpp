#include <bits/stdc++.h>

using namespace std;

int main(){
  vector<int> v{ 1, 2, 3, 4, 5};
  vector<int>::iterator it = std::find(v.begin(), v.end(), 4);
  v.insert(it, 7); // 1, 2, 3, 7, 4, 5
  it = v.begin() + 2;
  *it = 11; // 1, 2, 11, 7 , 4, 5
  vector<int> x;
  std::copy_if(v.begin(), v.end(), back_inserter(x), [](int a) { return a % 2 == 1; } ); // 1, 11, 7, 5

  for(auto a : x){
    cout << a << " ";
  }
  return 0;
}
