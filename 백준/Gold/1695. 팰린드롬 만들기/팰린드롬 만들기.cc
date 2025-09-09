#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int n;
vector<int> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  arr.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

int Count(int left, int right, vector<vector<int>>& dp) {
  if (left < 0 && right >= n)
    return 0;
  else if (left < 0)
    return n - right;
  else if (right >= n)
    return left + 1;

  if (dp[left][right] != -1)
    return dp[left][right];

  if (arr[left] == arr[right])
    return dp[left][right] = Count(left - 1, right + 1, dp);

  return dp[left][right] =
             min(Count(left - 1, right, dp), Count(left, right + 1, dp)) + 1;
}

void Solve() {
  vector<vector<int>> dp(n, vector<int>(n, -1));

  int min_count = numeric_limits<int>::max();
  for (int i = 0; i < n; ++i) {
    min_count = min(min_count, Count(i - 1, i + 1, dp));
    min_count = min(min_count, Count(i - 1, i + 1, dp));
    min_count = min(min_count, Count(i, i + 1, dp));
    min_count = min(min_count, Count(i, i + 1, dp));
  }

  cout << min_count << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
