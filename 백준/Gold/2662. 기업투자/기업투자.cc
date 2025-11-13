#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> profits(301, vector<int>(21));
vector<vector<int>> dp(21, vector<int>(301, -1));
vector<vector<int>> dp_elements(21, vector<int>(301));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= m; ++j)
      cin >> profits[i][j];
}

int DepthFirstSearch(int index, int money) {
  if (index > m)
    return 0;

  if (dp[index][money] != -1)
    return dp[index][money];

  int max_profit = 0;
  int max_invest = 0;
  for (int invest = 0; invest <= money; ++invest) {
    int profit =
        profits[invest][index] + DepthFirstSearch(index + 1, money - invest);

    if (profit > max_profit) {
      max_profit = profit;
      max_invest = invest;
    }
  }

  dp_elements[index][money] = max_invest;
  return dp[index][money] = max_profit;
}

void Solve() {
  cout << DepthFirstSearch(1, n) << '\n';

  int money = n;
  for (int i = 1; i <= m; ++i) {
    cout << dp_elements[i][money] << ' ';
    money -= dp_elements[i][money];
  }
  cout << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
