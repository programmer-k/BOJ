#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

int t;
vector<int64_t> arr;
vector<int> dp(100);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> t;

  arr.resize(t);
  for (int i = 0; i < t; ++i)
    cin >> arr[i];
}

int CalculateMinCoinCount(int64_t val) {
  int coin_count = 0;

  while (val > 0) {
    coin_count += dp[val % 100];
    val /= 100;
  }

  return coin_count;
}

void Solve() {
  for (int i = 1; i < 100; ++i) {
    dp[i] = dp[i - 1] + 1;

    if (i >= 10)
      dp[i] = min(dp[i], dp[i - 10] + 1);

    if (i >= 25)
      dp[i] = min(dp[i], dp[i - 25] + 1);
  }

  for (int64_t val : arr)
    cout << CalculateMinCoinCount(val) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
