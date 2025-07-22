#include <iostream>
#include <vector>
#include <utility>
using namespace std;

const int kMaxCost = 100'000;
int c, n;
vector<pair<int, int>> promotions;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> c >> n;
  for (int i = 0; i < n; ++i) {
    int cost, customer;
    cin >> cost >> customer;
    promotions.push_back({ cost, customer });
  }
}

void Solve() {
  vector<vector<int>> dp(n, vector<int>(kMaxCost + 1));
  
  for (int i = 0; i < n; ++i)
    for (int j = 0; j <= kMaxCost; ++j)
      dp[i][j] = max(i - 1 >= 0 ? dp[i - 1][j] : 0, j - promotions[i].first >= 0 ? dp[i][j - promotions[i].first] + promotions[i].second : 0);

  for (int i = 0; i <= kMaxCost; ++i)
    if (dp[n - 1][i] >= c) {
      cout << i << '\n';
      break;
    }
}

int main() {
  GetInput();
  Solve();
  return 0;
}