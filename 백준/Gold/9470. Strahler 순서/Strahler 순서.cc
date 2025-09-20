#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int t;
int k, m, p;
vector<vector<int>> edges;

void GetInput1() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> t;
}

void GetInput2() {
  cin >> k >> m >> p;

  edges.resize(m + 1);
  for (int i = 1; i <= m; ++i)
    edges[i].clear();

  for (int i = 0; i < p; ++i) {
    int a, b;
    cin >> a >> b;
    edges[a].push_back(b);
  }
}

void TopologicalSort() {
  queue<int> q;
  vector<int> in_degrees(m + 1);
  vector<pair<int, int>> answers(m + 1);

  for (int node = 1; node <= m; ++node)
    for (int next_node : edges[node])
      ++in_degrees[next_node];

  for (int i = 1; i <= m; ++i) {
    if (in_degrees[i] == 0) {
      q.push(i);
      answers[i].first = 1;
    }
  }

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int next_node : edges[node]) {
      if (answers[next_node].first < answers[node].first) {
        answers[next_node].first = answers[node].first;
        answers[next_node].second = 1;
      } else if (answers[next_node].first == answers[node].first) {
        ++answers[next_node].second;
      }

      if (--in_degrees[next_node] == 0) {
        q.push(next_node);
        if (answers[next_node].second >= 2) {
          ++answers[next_node].first;
        }
      }
    }
  }

  cout << k << ' ' << answers[m].first << '\n';
}

void Solve() {
  TopologicalSort();
}

int main() {
  GetInput1();
  for (int i = 0; i < t; ++i) {
    GetInput2();
    Solve();
  }
  return 0;
}
