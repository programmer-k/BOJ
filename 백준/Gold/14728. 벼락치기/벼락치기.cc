#include <iostream>
#include <utility>
#include <array>
using namespace std;

int n, t;
array<pair<int, int>, 101> studies;
array<array<int, 10'001>, 101> dp;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> t;
  for (int i = 1; i <= n; ++i)
    cin >> studies[i].first >> studies[i].second;
}

void Solve() {
  for (int i = 1; i <= 100; ++i) {
    for (int j = 0; j <= 10'000; ++j) {
      if (j - studies[i].first >= 0)
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - studies[i].first] + studies[i].second);
      else
        dp[i][j] = dp[i - 1][j];
    }
  }

  cout << dp[n][t] << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}