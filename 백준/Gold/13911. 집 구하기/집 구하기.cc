#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

const int64_t kInt64Max = numeric_limits<int64_t>::max();

int v, e, m, x, s, y;
vector<vector<pair<int, int>>> edges;
vector<int> mcdonalds, starbucks;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> v >> e;

  edges.resize(v + 1);
  for (int i = 0; i < e; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    edges[u].push_back({v, w});
    edges[v].push_back({u, w});
  }

  cin >> m >> x;

  mcdonalds.resize(m);
  for (int i = 0; i < m; ++i)
    cin >> mcdonalds[i];

  cin >> s >> y;

  starbucks.resize(s);
  for (int i = 0; i < s; ++i)
    cin >> starbucks[i];
}

vector<int64_t> Dijkstra(const vector<int>& starts) {
  priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>,
                 greater<pair<int64_t, int>>>
      pq;
  vector<int64_t> dists(v + 1, kInt64Max);

  for (int start : starts) {
    pq.push({0, start});
    dists[start] = 0;
  }

  while (!pq.empty()) {
    pair<int, int> p = pq.top();
    int64_t curr_dist = p.first;
    int curr_node = p.second;
    pq.pop();

    if (curr_dist > dists[curr_node])
      continue;

    for (const pair<int, int>& next : edges[curr_node]) {
      int next_node = next.first;
      int delta = next.second;
      int64_t next_dist = curr_dist + delta;

      if (next_dist < dists[next_node]) {
        pq.push({next_dist, next_node});
        dists[next_node] = next_dist;
      }
    }
  }

  return dists;
}

void Solve() {
  vector<int64_t> mcdonalds_dists = Dijkstra(mcdonalds);
  vector<int64_t> starbucks_dists = Dijkstra(starbucks);

  int64_t answer = kInt64Max;
  for (int i = 1; i <= v; ++i) {
    int64_t dist1 = mcdonalds_dists[i];
    int64_t dist2 = starbucks_dists[i];

    // Skip the node if it is not a house.
    if (dist1 == 0 || dist2 == 0)
      continue;

    if (dist1 <= x && dist2 <= y)
      answer = min(answer, dist1 + dist2);
  }

  if (answer != kInt64Max)
    cout << answer << '\n';
  else
    cout << "-1\n";
}

int main() {
  GetInput();
  Solve();
  return 0;
}
