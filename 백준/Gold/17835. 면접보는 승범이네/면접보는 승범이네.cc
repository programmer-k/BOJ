#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

const int64_t kInt64Max = numeric_limits<int64_t>::max();

int n, m, k;
vector<vector<pair<int, int>>> backward_edges;
vector<int> interview_cities;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> k;

  backward_edges.resize(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v, c;
    cin >> u >> v >> c;
    backward_edges[v].push_back({u, c});
  }

  interview_cities.resize(k);
  for (int i = 0; i < k; ++i)
    cin >> interview_cities[i];
}

void Dijkstra() {
  priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>,
                 greater<pair<int64_t, int>>>
      pq;
  vector<int64_t> dists(n + 1, kInt64Max);

  for (int interview_city : interview_cities) {
    pq.push({0, interview_city});
    dists[interview_city] = 0;
  }

  while (!pq.empty()) {
    pair<int64_t, int> p = pq.top();
    int64_t curr_dist = p.first;
    int curr_node = p.second;
    pq.pop();

    if (dists[curr_node] < curr_dist)
      continue;

    for (const pair<int, int>& next : backward_edges[curr_node]) {
      int next_node = next.first;
      int delta = next.second;
      int64_t next_dist = curr_dist + delta;

      if (next_dist < dists[next_node]) {
        pq.push({next_dist, next_node});
        dists[next_node] = next_dist;
      }
    }
  }

  int64_t max_distance = *max_element(dists.begin() + 1, dists.end());
  cout << find(dists.begin() + 1, dists.end(), max_distance) - dists.begin()
       << '\n';
  cout << max_distance << '\n';
}

void Solve() {
  Dijkstra();
}

int main() {
  GetInput();
  Solve();
  return 0;
}
