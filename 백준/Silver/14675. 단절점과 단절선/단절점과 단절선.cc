#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int n, q;
vector<vector<int>> graph(100'001, vector<int>());
vector<pair<int, int>> queries;
vector<bool> visited(100'001, false);
vector<bool> isCutVertex(100'001, true);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  cin >> q;
  for (int i = 0; i < q; ++i) {
    int t, k;
    cin >> t >> k;
    queries.emplace_back(t, k);
  }
}

void MarkCutVertex(int node) {
  visited[node] = true;
  if (graph[node].size() == 1)
    isCutVertex[node] = false;

  for (int next_node : graph[node]) {
    if (!visited[next_node]) {
      MarkCutVertex(next_node);
    }
  }
}

void Solve() {
  MarkCutVertex(1);

  for (int i = 0; i < q; ++i) {
    int t = queries[i].first;
    int k = queries[i].second;

    if (t == 1) {
      if (isCutVertex[k]) {
        cout << "yes\n";
      } else {
        cout << "no\n";
      }
    } else {
      cout << "yes\n";
    }
  }
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}