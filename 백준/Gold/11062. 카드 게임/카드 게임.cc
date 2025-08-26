#include <iostream>
#include <vector>
using namespace std;

int t, n;
vector<int> arr(1'001);
vector<int> prefix_sum(1'001);

void GetInput1() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> t;
}

void GetInput2() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> arr[i];
}

int CalculateMaximumScore(int from, int to, vector<vector<int>>& dp) {
  if (dp[from][to] != -1)
    return dp[from][to];

  if (from == to)
    return dp[from][to] = arr[from];

  int candidate1 = prefix_sum[to] - prefix_sum[from] -
                   CalculateMaximumScore(from + 1, to, dp) + arr[from];
  int candidate2 = prefix_sum[to - 1] - prefix_sum[from - 1] -
                   CalculateMaximumScore(from, to - 1, dp) + arr[to];
  return dp[from][to] = max(candidate1, candidate2);
}

void Solve() {
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

  prefix_sum[0] = 0;
  for (int i = 1; i <= n; ++i)
    prefix_sum[i] = prefix_sum[i - 1] + arr[i];

  cout << CalculateMaximumScore(1, n, dp) << '\n';
}

int main() {
  GetInput1();
  for (int i = 0; i < t; ++i) {
    GetInput2();
    Solve();
  }
  return 0;
}
