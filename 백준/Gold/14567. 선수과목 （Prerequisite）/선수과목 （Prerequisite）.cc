#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int n, m;
vector<vector<int>> edges(1'001);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    edges[a].push_back(b);
  }
}

void TopologicalSort() {
  queue<int> q;
  vector<int> in_degrees(n + 1), semesters(n + 1);

  for (int i = 1; i <= n; ++i) {
    for (int next_node : edges[i]) {
      ++in_degrees[next_node];
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (in_degrees[i] == 0) {
      q.push(i);
      semesters[i] = 1;
    }
  }

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int next_node : edges[node]) {
      if (--in_degrees[next_node] == 0) {
        q.push(next_node);
        semesters[next_node] = semesters[node] + 1;
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    cout << semesters[i] << ' ';
  }
  cout << '\n';
}

void Solve() {
  TopologicalSort();
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}