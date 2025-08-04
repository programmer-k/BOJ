#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> parents;
vector<pair<int, int>> praises;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  parents.resize(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> parents[i];

  praises.resize(m);
  for (int i = 0; i < m; ++i)
    cin >> praises[i].first >> praises[i].second;
}

void Solve() {
  vector<int> total_praises(n + 1);

  for (const pair<int, int>& praise : praises) {
    int worker_num = praise.first;
    int praise_val = praise.second;
    total_praises[worker_num] += praise_val;
  }

  for (int i = 2; i <= n; ++i)
    total_praises[i] += total_praises[parents[i]];

  for (int i = 1; i <= n; ++i)
    cout << total_praises[i] << ' ';
  cout << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
