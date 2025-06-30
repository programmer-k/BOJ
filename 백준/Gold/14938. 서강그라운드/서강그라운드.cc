#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
#include <limits>
using namespace std;

int n, m, r;
array<int, 101> items;
vector<vector<pair<int, int>>> edges(101);

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> r;
  for (int i = 1; i <= n; ++i)
    cin >> items[i];
  
  for (int i = 0; i < r; ++i) {
    int a, b, l;
    cin >> a >> b >> l;
    edges[a].push_back({ b, l });
    edges[b].push_back({ a, l });
  }
}

int Dijkstra(int start) {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  vector<int> dists(n + 1, numeric_limits<int>::max());
  pq.push({ 0, start });
  dists[start] = 0;

  while (!pq.empty()) {
    pair<int, int> p = pq.top();
    int curr_dist = p.first;
    int curr_node = p.second;
    pq.pop();

    if (curr_dist > dists[curr_node])
      continue;
    
    for (pair<int, int> next : edges[curr_node]) {
      int next_node = next.first;
      int append_dist = next.second;
      int next_dist = curr_dist + append_dist;

      if (next_dist < dists[next_node]) {
        pq.push({ next_dist, next_node });
        dists[next_node] = next_dist;
      }
    }
  }

  int total = 0;
  for (int i = 1; i <= n; ++i)
    if (dists[i] <= m)
      total += items[i];
  return total;
}

void Solve() {
  int max_val = 0;
  for (int i = 1; i <= n; ++i)
    max_val = max(max_val, Dijkstra(i));
  cout << max_val << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}