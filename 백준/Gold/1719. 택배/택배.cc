#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <functional>
using namespace std;

const int kIntMax = numeric_limits<int>::max();
int n, m;
vector<vector<pair<int, int>>> edges;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  edges.resize(n + 1);
  for (int i = 0; i < m; ++i) {
    int node1, node2, t;
    cin >> node1 >> node2 >> t;
    edges[node1].push_back({ node2, t });
    edges[node2].push_back({ node1, t });
  }
}

void Dijkstra(int start, vector<int>& answer) {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  vector<int> dists(n + 1, kIntMax);
  vector<int> prevs(n + 1);
  pq.push({ 0, start });
  dists[start] = 0;
  prevs[start] = start;

  while (!pq.empty()) {
    pair<int, int> p = pq.top();
    int curr_dist = p.first;
    int curr_node = p.second;
    pq.pop();

    if (dists[curr_node] < curr_dist)
      continue;
    
    for (const pair<int, int>& next : edges[curr_node]) {
      int next_node = next.first;
      int next_step = next.second;
      int next_dist = curr_dist + next_step;

      if (next_dist < dists[next_node]) {
        pq.push({ next_dist, next_node });
        dists[next_node] = next_dist;
        prevs[next_node] = curr_node;
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    int node = i;
    while (prevs[node] != start)
      node = prevs[node];
    answer[i] = node;
  }
}

void Solve() {
  vector<vector<int>> answer(n + 1, vector<int>(n + 1));
  for (int i = 1; i <= n; ++i) {
    Dijkstra(i, answer[i]);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (i == j) {
        cout << "- ";
      } else {
        cout << answer[i][j] << ' ';
      }
    }
    cout << '\n';
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
