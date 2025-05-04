#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> edges(100'001);
vector<vector<int64_t>> dist(2, vector<int64_t>(100'001, numeric_limits<int64_t>::max()));
priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> pq;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    edges[u].push_back({ v, w });
    edges[v].push_back({ u, w });
  }
}

void Dijkstra() {
  pq.push({ 0, 1 });
  dist[0][1] = 0;

  while (!pq.empty()) {
    pair<int64_t, int> p = pq.top();
    int64_t curr_dist = p.first;
    int curr_node = p.second;
    pq.pop();

    if (dist[curr_dist % 2][curr_node] < curr_dist)
      continue;
    
    for (pair<int, int> next : edges[curr_node]) {
      int next_node = next.first;
      int delta = next.second;
      int64_t next_dist = curr_dist + delta;

      if (next_dist < dist[next_dist % 2][next_node]) {
        pq.push({ next_dist, next_node });
        dist[next_dist % 2][next_node] = next_dist;
      }
    }
  }
}

int64_t Convert(int64_t val) {
  if (val == numeric_limits<int64_t>::max())
    return -1;
  return val;
}

void Solve() {
  Dijkstra();
  for (int i = 1; i <= n; ++i) {
    cout << Convert(dist[1][i]) << ' ' << Convert(dist[0][i]) << '\n';
  }
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}