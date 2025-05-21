#include <iostream>
#include <array>
#include <algorithm>
#include <limits>
using namespace std;

int n;
array<int, 100'000> arr;
array<array<int, 100'000>, 2> dp;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void Solve() {
  dp[0][0] = dp[1][0] = arr[0];
  dp[0][1] = dp[1][1] = max(arr[0] + arr[1], arr[1]);

  for (int i = 2; i < n; ++i) {
    dp[0][i] = max(arr[i], dp[0][i - 1] + arr[i]);
    dp[1][i] = max({ dp[0][i - 2] + arr[i], dp[1][i - 1] + arr[i] });
  }

  int max_val = numeric_limits<int>::min();
  for (int i = 0; i < n; ++i) {
    max_val = max({ max_val, dp[0][i], dp[1][i] });
  }

  cout << max_val << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}