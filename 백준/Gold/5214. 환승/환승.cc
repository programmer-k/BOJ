#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, k, m;
vector<vector<int>> edges(101'001);
vector<vector<int>> hyper_tubes(1'000, vector<int>(1'000));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> k >> m;

  for (int i = 0; i < m; ++i)
    for (int j = 0; j < k; ++j)
      cin >> hyper_tubes[i][j];
}

int BreadthFirstSearch() {
  queue<int> q;
  vector<int> visited(n + 1, -1);
  q.push(1);
  visited[1] = 1;

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int next_hyper_tube : edges[node]) {
      for (int next_node : edges[next_hyper_tube]) {
        if (visited[next_node] == -1) {
          q.push(next_node);
          visited[next_node] = visited[node] + 1;
        }
      }
    }
  }

  return visited[n];
}

void Solve() {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < k; ++j) {
      int node = hyper_tubes[i][j];
      int hyper_tube = n + i + 1;
      edges[node].push_back(hyper_tube);
      edges[hyper_tube].push_back(node);
    }
  }

  cout << BreadthFirstSearch() << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
