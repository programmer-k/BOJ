#include <iostream>
#include <array>
#include <vector>
using namespace std;

int n, r, q;
vector<vector<int>> graph(100'001);
array<int, 100'000> u;
vector<int> visited(100'001);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> r >> q;
  for (int i = 0; i < n - 1; ++i) {
    int node1, node2;
    cin >> node1 >> node2;
    graph[node1].push_back(node2);
    graph[node2].push_back(node1);
  }
  for (int i = 0; i < q; ++i)
    cin >> u[i];
}

int DepthFirstSearch(int node) {
  visited[node] = 1;
  for (int next_node : graph[node]) {
    if (visited[next_node] == 0) {
      visited[node] += DepthFirstSearch(next_node);
    }
  }
  return visited[node];
}

void Solve() {
  DepthFirstSearch(r);
  for (int i = 0; i < q; ++i) {
    cout << visited[u[i]] << '\n';
  }
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}