#include <iostream>
#include <string>
using namespace std;

int t;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> t;
}

bool IsValid(const string& str, int index) {
  if (index == ssize(str))
    return true;
  
  string first_two = str.substr(index, 2);
  
  if (first_two == "01") {
    return IsValid(str, index + 2);
  } else if (first_two == "10") {
    index += 2;

    int zero_count = 0;
    while (index < ssize(str) && str[index] == '0') {
      ++index;
      ++zero_count;
    }

    int one_count = 0;
    while (index < ssize(str) && str[index] == '1') {
      ++index;
      ++one_count;
    }

    if (zero_count == 0 || one_count == 0)
      return false;

    if (one_count == 1)
      return IsValid(str, index);
    else
      return IsValid(str, index - 1) || IsValid(str, index);
  }

  return false;
}

void Solve() {
  string input;
  cin >> input;

  cout << (IsValid(input, 0) ? "YES" : "NO") << '\n';
}

int main(void) {
  GetInput();
  for (int i = 0; i < t; ++i)
    Solve();
  return 0;
}