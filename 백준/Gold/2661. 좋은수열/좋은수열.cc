#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int n;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n;
}

void DepthFirstSearch(string& str) {
  for (int i = 1; ssize(str) - i * 2 >= 0; ++i) {
    string sub1 = str.substr(ssize(str) - i, i);
    string sub2 = str.substr(ssize(str) - i * 2, i);
    
    if (sub1 == sub2)
      return;
  }
  
  if (ssize(str) == n) {
    cout << str << '\n';
    exit(0);
  }

  for (char ch = '1'; ch <= '3'; ++ch) {
    str.push_back(ch);
    DepthFirstSearch(str);
    str.pop_back();
  }
}

void Solve() {
  string str;
  DepthFirstSearch(str);
}

int main() {
  GetInput();
  Solve();
  return 0;
}