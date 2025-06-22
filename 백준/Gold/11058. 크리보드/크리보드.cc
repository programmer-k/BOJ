#include <iostream>
#include <string>
#include <array>
#include <cstdint>
using namespace std;

int n;
array<int64_t, 101> dp;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
}

void Solve() {
  for (int i = 1; i <= n; ++i) {
    dp[i] = dp[i - 1] + 1;

    for (int j = 0; i - 3 - j >= 0; ++j)
      dp[i] = max(dp[i], dp[i - 3 - j] * (j + 2));
  }

  cout << dp[n] << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}