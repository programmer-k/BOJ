#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<int>> edges;
vector<int> visit_orders, visit_indices, answers;
vector<bool> visited;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  edges.resize(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    int node1, node2;
    cin >> node1 >> node2;
    edges[node1].push_back(node2);
    edges[node2].push_back(node1);
  }

  visit_orders.resize(n);
  visit_indices.resize(n + 1);
  for (int i = 0; i < n; ++i) {
    cin >> visit_orders[i];
    visit_indices[visit_orders[i]] = i;
  }
}

bool Compare(int node1, int node2) {
  return visit_indices[node1] < visit_indices[node2];
}

void DepthFirstSearch(int node) {
  visited[node] = true;
  answers.push_back(node);

  for (int next_node : edges[node])
    if (!visited[next_node])
      DepthFirstSearch(next_node);
}

void Solve() {
  for (int i = 1; i <= n; ++i)
    sort(edges[i].begin(), edges[i].end(), Compare);

  visited.resize(n + 1);
  DepthFirstSearch(1);

  if (answers == visit_orders)
    cout << "1\n";
  else
    cout << "0\n";
}

int main() {
  GetInput();
  Solve();
  return 0;
}
