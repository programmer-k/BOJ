#include <iostream>
#include <vector>
#include <array>
#include <utility>
#include <queue>
#include <functional>
#include <limits>
using namespace std;

int n, m;
array<vector<pair<int, int>>, 50'001> edges;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int node1, node2, weight;
    cin >> node1 >> node2 >> weight;
    edges[node1].push_back({ weight, node2 });
    edges[node2].push_back({ weight, node1 });
  }
}

int Dijkstra() {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  vector<int> dists(n + 1, numeric_limits<int>::max());
  pq.push({ 0, 1 });
  dists[1] = 0;

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

  return dists[n];
}

void Solve() {
  cout << Dijkstra() << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}