#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string str1, str2, str3;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> str1 >> str2 >> str3;
}

int Get(const vector<vector<vector<int>>>& dp, int i, int j, int k) {
  if (i >= 0 && j >= 0 && k >= 0)
    return dp[i][j][k];
  return 0;
}

void LongestCommonSubsequence(const string& s1, const string& s2, const string& s3) {
  vector<vector<vector<int>>> dp(ssize(s1), vector<vector<int>>(ssize(s2), vector<int>(ssize(s3))));

  for (int i = 0; i < ssize(s1); ++i) {
    for (int j = 0; j < ssize(s2); ++j) {
      for (int k = 0; k < ssize(s3); ++k) {
        if (s1[i] == s2[j] && s2[j] == s3[k]) {
          dp[i][j][k] = Get(dp, i - 1, j - 1, k - 1) + 1;
        } else {
          dp[i][j][k] = max({ Get(dp, i - 1, j, k), Get(dp, i, j - 1, k), Get(dp, i, j, k - 1) });
        }
      }
    }
  }

  cout << dp[ssize(s1) - 1][ssize(s2) - 1][ssize(s3) - 1] << '\n';
}

void Solve() {
  LongestCommonSubsequence(str1, str2, str3);
}

int main() {
  GetInput();
  Solve();
  return 0;
}
