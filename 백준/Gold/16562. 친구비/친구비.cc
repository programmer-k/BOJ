#include <iostream>
#include <array>
#include <vector>
using namespace std;

int n, m, k;
array<int, 10'001> a;
vector<vector<int>> edges(10'001);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> k;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];

  for (int i = 0; i < m; ++i) {
    int v, w;
    cin >> v >> w;
    edges[v].push_back(w);
    edges[w].push_back(v);
  }
}

int DepthFirstSearch(int node, vector<bool>& visited) {
  int min_cost = a[node];
  visited[node] = true;
  for (int next_node : edges[node])
    if (!visited[next_node])
      min_cost = min(min_cost, DepthFirstSearch(next_node, visited));
  return min_cost;
}

void Solve() {
  int total_cost = 0;
  vector<bool> visited(n + 1);
  
  for (int i = 1; i <= n; ++i)
    if (!visited[i])
      total_cost += DepthFirstSearch(i, visited);

  if (k >= total_cost)
    cout << total_cost << '\n';
  else
    cout << "Oh no\n";
}

int main() {
  GetInput();
  Solve();
  return 0;
}