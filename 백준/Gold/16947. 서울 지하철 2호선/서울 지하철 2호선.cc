#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> edges;
vector<bool> visited, is_circular_line;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  edges.resize(n + 1);
  for (int i = 0; i < n; ++i) {
    int node1, node2;
    cin >> node1 >> node2;
    edges[node1].push_back(node2);
    edges[node2].push_back(node1);
  }
}

bool DepthFirstSearch(int node, int prev_node, int revisit_node) {
  visited[node] = true;
  bool ret = false;
  for (int next_node : edges[node]) {
    if (!visited[next_node])
      ret |= DepthFirstSearch(next_node, node, revisit_node);
    
    if (prev_node != revisit_node && next_node == revisit_node)
      ret = true;
  }

  if (ret)
    return is_circular_line[node] = true;
  return false;
}

void BreathFirstSearch() {
  queue<int> q;
  vector<int> dists(n + 1, -1);
  
  for (int i = 1; i <= n; ++i) {
    if (is_circular_line[i]) {
      q.push(i);
      dists[i] = 0;
    }
  }

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int next_node : edges[node]) {
      if (dists[next_node] == -1) {
        q.push(next_node);
        dists[next_node] = dists[node] + 1;
      }
    }
  }

  for (int i = 1; i <= n; ++i)
    cout << dists[i] << ' ';
  cout << '\n';
}

void Solve() {
  visited.resize(n + 1);
  is_circular_line.resize(n + 1);
  
  for (int i = 1; i <= n; ++i) {
    if (!is_circular_line[i]) {
      fill(visited.begin(), visited.end(), false);
      DepthFirstSearch(i, -1, i);
    }
  }

  BreathFirstSearch();
}

int main() {
  GetInput();
  Solve();
  return 0;
}
