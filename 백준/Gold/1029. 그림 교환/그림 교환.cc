#include <cstring>
#include <iostream>
using namespace std;

int n;
char prices[15][15];
int dp[1 << 15][15]['9' + 1];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> prices[i][j];
}

int CalculateMaxCount(int state, int prev, int prev_price) {
  if (dp[state][prev][prev_price] != -1)
    return dp[state][prev][prev_price];

  int max_count = 1;
  for (int i = 0; i < n; ++i) {
    int val = 1 << i;

    if ((state & val) == 0 && prices[prev][i] >= prev_price)
      max_count = max(max_count,
                      CalculateMaxCount(state | val, i, prices[prev][i]) + 1);
  }

  return dp[state][prev][prev_price] = max_count;
}

void Solve() {
  memset(dp, -1, sizeof(dp));
  cout << CalculateMaxCount(1, 0, '0') << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
