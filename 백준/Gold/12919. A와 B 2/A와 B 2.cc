#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string s, t;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> s >> t;
}

bool IsConvertable(string from) {
  if (from.size() == s.size()) {
    if (from == s)
      return true;
    else
      return false;
  }

  if (from.back() == 'A' && IsConvertable(from.substr(0, from.size() - 1)))
    return true;
  
  if (from.front() == 'B') {
    string str = from.substr(1, from.size() - 1);
    reverse(str.begin(), str.end());
    
    if (IsConvertable(str))
      return true;
  }

  return false;
}

void Solve() {
  cout << IsConvertable(t) << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}