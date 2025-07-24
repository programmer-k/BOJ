#include <iostream>
#include <string>
#include <limits>
using namespace std;

int n;
string str1, str2;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  cin >> str1 >> str2;
}

char Switch(char val) {
  if (val == '0')
    return '1';
  else
    return '0';
}

void Solve() {
  int answer = numeric_limits<int>::max();

  for (int j = 0; j < 2; ++j) {
    int switch_count = 0;
    string str1_copy = str1;
    
    if (j == 1) {
      str1_copy[0] = Switch(str1_copy[0]);
      str1_copy[1] = Switch(str1_copy[1]);
      ++switch_count;
    }

    for (int i = 1; i < n - 1; ++i) {
      if (str1_copy[i - 1] != str2[i - 1]) {
        str1_copy[i - 1] = Switch(str1_copy[i - 1]);
        str1_copy[i] = Switch(str1_copy[i]);
        str1_copy[i + 1] = Switch(str1_copy[i + 1]);
        ++switch_count;
      }
    }

    for (int k = 0; k < 2; ++k) {
      if (k == 1) {
        str1_copy[n - 1] = Switch(str1_copy[n - 1]);
        str1_copy[n - 2] = Switch(str1_copy[n - 2]);
        ++switch_count;
      }

      if (str1_copy == str2) {
        answer = min(answer, switch_count);
      }
    }  
  }

  if (answer == numeric_limits<int>::max())
    cout << "-1\n";
  else
    cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}