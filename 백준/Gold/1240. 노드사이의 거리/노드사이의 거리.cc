#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> edges(1'001);
vector<pair<int, int>> node_pairs(1'000);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < n - 1; ++i) {
    int node1, node2, dist;
    cin >> node1 >> node2 >> dist;
    edges[node1].push_back({ dist, node2 });
    edges[node2].push_back({ dist, node1 });
  }

  for (int i = 0; i < m; ++i)
    cin >> node_pairs[i].first >> node_pairs[i].second;
}

int Dijkstra(int from, int to) {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  vector<int> dists(n + 1, numeric_limits<int>::max());
  pq.push({ 0, from });
  dists[from] = 0;

  while (!pq.empty()) {
    pair<int, int> p = pq.top();
    int curr_dist = p.first;
    int curr_node = p.second;
    pq.pop();

    if (curr_dist > dists[curr_node])
      continue;
    
    for (pair<int, int> next : edges[curr_node]) {
      int next_step = next.first;
      int next_node = next.second;
      int next_dist = curr_dist + next_step;

      if (next_dist < dists[next_node]) {
        pq.push({ next_dist, next_node });
        dists[next_node] = next_dist;
      }
    }
  }

  return dists[to];
}

void Solve() {
  for (int i = 0; i < m; ++i) {
    cout << Dijkstra(node_pairs[i].first, node_pairs[i].second) << '\n';
  }
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}