#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int n, m, answer;
vector<vector<int>> friend_edges, enemy_edges;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  cin >> m;

  friend_edges.resize(n + 1);
  enemy_edges.resize(n + 1);

  for (int i = 0; i < m; ++i) {
    char ch;
    int p, q;
    cin >> ch >> p >> q;

    if (ch == 'F') {
      friend_edges[p].push_back(q);
      friend_edges[q].push_back(p);
    } else {
      enemy_edges[p].push_back(q);
      enemy_edges[q].push_back(p);
    }
  }
}

void BreadthFirstSearch(int start, vector<bool>& visited) {
  queue<int> q;
  q.push(start);
  visited[start] = true;

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int next_node : friend_edges[node]) {
      if (!visited[next_node]) {
        q.push(next_node);
        visited[next_node] = true;
      }
    }
  }

  ++answer;
}

void CalculateFriendEdgesFromEnemyEdges() {
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < ssize(enemy_edges[i]); ++j) {
      for (int k = j + 1; k < ssize(enemy_edges[i]); ++k) {
        int node1 = enemy_edges[i][j];
        int node2 = enemy_edges[i][k];
        friend_edges[node1].push_back(node2);
        friend_edges[node2].push_back(node1);
      }
    }
  }
}

void Solve() {
  CalculateFriendEdgesFromEnemyEdges();

  vector<bool> visited(n + 1);
  for (int i = 1; i <= n; ++i)
    if (!visited[i])
      BreadthFirstSearch(i, visited);

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
