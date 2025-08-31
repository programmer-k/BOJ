#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

const int kDivisor = 1'000'000'000;
int n;
vector<int64_t> dp(1'000'001);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n;
}

void Solve() {
  dp[2] = 1;

  for (int i = 3; i <= n; ++i)
    dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]) % kDivisor;

  cout << dp[n] << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
