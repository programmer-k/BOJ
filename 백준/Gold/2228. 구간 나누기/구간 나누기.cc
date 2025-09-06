#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int n, m;
vector<int> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  arr.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

int CalculateMaximum(int index_n, int index_m, vector<vector<int>>& dp) {
  if (index_m == m)
    return 0;

  if (index_n >= n)
    return numeric_limits<int>::min() + 1;

  if (dp[index_n][index_m] != numeric_limits<int>::min())
    return dp[index_n][index_m];

  int max_val = numeric_limits<int>::min() + 1;
  for (int i = index_n; i < n; ++i) {
    int total = 0;
    for (int j = i; j < n; ++j) {
      total += arr[j];
      int next_total = CalculateMaximum(j + 2, index_m + 1, dp);
      
      if (next_total == numeric_limits<int>::min() + 1)
        break;
      
      max_val = max(max_val, total + next_total);
    }
  }

  return dp[index_n][index_m] = max_val;
}

void Solve() {
  vector<vector<int>> dp(n, vector<int>(m, numeric_limits<int>::min()));
  cout << CalculateMaximum(0, 0, dp) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
