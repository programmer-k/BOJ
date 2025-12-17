#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int n;
vector<int> arr;
vector<int> groups(4);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  arr.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

int64_t Calculate(int group_index, int arr_index, int part_sum,
                  vector<vector<int64_t>>& dp) {
  if (group_index == 4 && arr_index == n)
    return 1;
  else if (group_index >= 4 || arr_index >= n)
    return 0;

  if (dp[group_index][arr_index] != -1)
    return dp[group_index][arr_index];

  int64_t count = 0;
  groups[group_index] += arr[arr_index];
  if (groups[group_index] == part_sum)
    count += Calculate(group_index + 1, arr_index + 1, part_sum, dp);
  count += Calculate(group_index, arr_index + 1, part_sum, dp);
  groups[group_index] -= arr[arr_index];

  return dp[group_index][arr_index] = count;
}

void Solve() {
  vector<vector<int64_t>> dp(4, vector<int64_t>(n, -1));
  int sum = accumulate(arr.begin(), arr.end(), 0);

  if (sum % 4 == 0)
    cout << Calculate(0, 0, sum / 4, dp) << '\n';
  else
    cout << "0\n";
}

int main() {
  GetInput();
  Solve();
  return 0;
}
