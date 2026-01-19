#include <iostream>
#include <utility>
using namespace std;

int m, q;
int arr[200'001];
pair<int, int> queries[200'000];
int dp[200'001][19];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> m;

  for (int i = 1; i <= m; ++i)
    cin >> dp[i][0];

  cin >> q;

  for (int i = 0; i < q; ++i)
    cin >> queries[i].first >> queries[i].second;
}

void Solve() {
  for (int j = 1; j < 19; ++j)
    for (int i = 1; i <= m; ++i)
      dp[i][j] = dp[dp[i][j - 1]][j - 1];

  for (int i = 0; i < q; ++i) {
    int count = 0;
    int n = queries[i].first;
    int x = queries[i].second;

    while (n > 0) {
      if (n % 2 == 1)
        x = dp[x][count];

      n /= 2;
      ++count;
    }

    cout << x << '\n';
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
