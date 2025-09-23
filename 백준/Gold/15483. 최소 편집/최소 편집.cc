#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string str1, str2;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> str1 >> str2;
}

void Solve() {
  str1.insert(str1.begin(), ' ');
  str2.insert(str2.begin(), ' ');
  vector<vector<int>> dp(ssize(str1), vector<int>(ssize(str2)));

  for (int i = 1; i < ssize(str1); ++i)
    dp[i][0] = i;

  for (int j = 1; j < ssize(str2); ++j)
    dp[0][j] = j;

  for (int i = 1; i < ssize(str1); ++i) {
    for (int j = 1; j < ssize(str2); ++j) {
      if (str1[i] == str2[j]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
      }
    }
  }

  cout << dp[ssize(str1) - 1][ssize(str2) - 1] << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
