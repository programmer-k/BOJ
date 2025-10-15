#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int test_case, n;
vector<int64_t> dp(101, numeric_limits<int64_t>::max());

void GetInput1() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> test_case;
}

void GetInput2() {
  cin >> n;
}

void CalculateMin() {
  dp[2] = 1;
  dp[3] = 7;
  dp[4] = 4;
  dp[5] = 2;
  dp[6] = 6;
  dp[7] = 8;
  dp[8] = 10;

  vector<int> min_nums = {0, 0, 1, 7, 4, 2, 0, 8};
  for (int i = 9; i <= 100; ++i)
    for (int j = 2; j <= 7; ++j)
      dp[i] = min(dp[i], dp[i - j] * 10 + min_nums[j]);
}

void CalculateMax(int num) {
  if (num % 2 == 1) {
    cout << '7';
    num -= 3;
  }

  for (int i = 0; i < num / 2; ++i)
    cout << '1';
}

void Solve() {
  cout << dp[n] << ' ';
  CalculateMax(n);
  cout << '\n';
}

int main() {
  CalculateMin();
  GetInput1();
  for (int i = 0; i < test_case; ++i) {
    GetInput2();
    Solve();
  }
  return 0;
}
