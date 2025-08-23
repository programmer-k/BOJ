#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<int> arr(50'001);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> arr[i];
  cin >> k;
}

void Solve() {
  vector<int> acc(n + 1);
  vector<vector<int>> dp(n + 1, vector<int>(4));

  int sum = 0;
  for (int i = 1; i < k; ++i)
    sum += arr[i];
  
  for (int i = k; i <= n; ++i) {
    sum += arr[i];
    sum -= arr[i - k];
    acc[i] = sum;
  }

  for (int j = 1; j <= 3; ++j)
    for (int i = k * j; i <= n; ++i)
      dp[i][j] = max(dp[i - 1][j], dp[i - k][j - 1] + acc[i]);

  cout << dp[n][3] << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
