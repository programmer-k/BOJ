#include <iostream>
#include <set>
#include <array>
#include <vector>
using namespace std;

int t;
vector<int> n;
array<array<int, 4>, 10'001> dp;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  
  cin >> t;
  for (int i = 0; i < t; ++i) {
    int val;
    cin >> val;
    n.push_back(val);
  }
}

void Calc() {
  dp[1][1] = 1;
  dp[2][1] = dp[2][2] = 1;
  dp[3][1] = dp[3][2] = dp[3][3] = 1;

  for (int i = 4; i <= 10'000; ++i) {
    for (int j = 1; j <= 3; ++j) {
      for (int k = 1; k <= j; ++k) {
        dp[i][j] += dp[i - j][k];
      }
    }
  }

  for (int i = 1; i <= 10'000; ++i)
    for (int j = 1; j <= 3; ++j)
      dp[i][0] += dp[i][j];
}

void Solve() {
  for (int i = 0; i < t; ++i) {
    int val = n[i];
    cout << dp[val][0] << '\n';
  }
}

int main(void) {
  Calc();
  GetInput();
  Solve();
  return 0;
}