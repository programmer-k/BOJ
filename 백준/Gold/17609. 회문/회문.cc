#include <iostream>
#include <array>
#include <string>
using namespace std;

int t;
array<string, 30> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> t;
  for (int i = 0; i < t; ++i)
    cin >> arr[i];
}

bool IsPalindrome(const string& str) {
  int len = ssize(str);
  for (int i = 0; i < len / 2; ++i)
    if (str[i] != str[len - 1 - i])
      return false;
  return true;
}

bool IsPseudoPalindrome(const string& str) {
  int len = ssize(str);
  for (int i = 0; i < len / 2; ++i) {
    if (str[i] != str[len - 1 - i]) {
      string str1(str.begin() + i, str.begin() + len - 1 - i);
      string str2(str.begin() + i + 1, str.begin() + len - i);
      return IsPalindrome(str1) || IsPalindrome(str2);
    }
  }
  return false;
}

void Solve() {
  for (int i = 0; i < t; ++i) {
    string& str = arr[i];
    if (IsPalindrome(str))
      cout << "0\n";
    else if (IsPseudoPalindrome(str))
      cout << "1\n";
    else
      cout << "2\n";
  }
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}