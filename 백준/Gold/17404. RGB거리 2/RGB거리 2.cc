#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
using namespace std;

int n;
array<array<int, 3>, 1'001> costs;
array<array<array<int, 3>, 1'001>, 3> dp;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j < 3; ++j)  
      cin >> costs[i][j];
}

int CalculateMinCost(int index, int prev_color, int first_color) {
  if (index == 0) {
    return 0;
  }

  if (dp[first_color][index][prev_color] != 0)
    return dp[first_color][index][prev_color];
  
  vector<int> candidates;
  for (int i = 0; i < 3; ++i) {
    if (prev_color != i) {
      if (index != 1 || (index == 1 && i != first_color)) {
        int val = CalculateMinCost(index - 1, i, first_color) + costs[index][i];
        candidates.push_back(val);
      }
    }
  }

  return dp[first_color][index][prev_color] = *min_element(candidates.begin(), candidates.end());
}

void Solve() {
  int val1 = CalculateMinCost(n - 1, 0, 0) + costs[n][0];
  int val2 = CalculateMinCost(n - 1, 1, 1) + costs[n][1];
  int val3 = CalculateMinCost(n - 1, 2, 2) + costs[n][2];

  cout << min({ val1, val2, val3 }) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}