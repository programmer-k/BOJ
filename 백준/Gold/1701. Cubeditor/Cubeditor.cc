#include <iostream>
#include <string>
#include <vector>
using namespace std;

string str;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> str;
}

int computeLPSMax(const string &s) {
  int m = s.size();
  vector<int> lps(m, 0);
  int len = 0, i = 1, ans = 0;

  while (i < m) {
    if (s[i] == s[len]) {
      len++;
      lps[i] = len;
      ans = max(ans, lps[i]);
      i++;
    } else {
      if (len != 0) {
        len = lps[len - 1];  // 되돌아가기
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }
  return ans;
}

void Solve() {
  int answer = 0;
  for (int i = 0; i < ssize(str); ++i)
    answer = max(answer, computeLPSMax(str.substr(i)));
  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
