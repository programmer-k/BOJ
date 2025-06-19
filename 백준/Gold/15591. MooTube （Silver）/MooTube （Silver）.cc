#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int n, q;
vector<vector<pair<int, int>>> edges(5'001);
vector<pair<int, int>> questions;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> q;
  for (int i = 0; i < n - 1; ++i) {
    int p, q, r;
    cin >> p >> q >> r;
    edges[p].push_back({ q, r });
    edges[q].push_back({ p, r });
  }

  for (int i = 0; i < q; ++i) {
    int k, v;
    cin >> k >> v;
    questions.push_back({ k, v });
  }
}

void DepthFirstSearch(int node, int min_val, vector<int>& visited) {
  visited[node] = min_val;
  for (pair<int, int> next_node : edges[node]) {
    if (visited[next_node.first] == -1) {
      DepthFirstSearch(next_node.first, min(min_val, next_node.second), visited);
    }
  }
}

void Solve() {
  for (pair<int, int> p : questions) {
    vector<int> visited(n + 1, -1);
    DepthFirstSearch(p.second, 1'234'567'890, visited);

    int answer = 0;
    for (int val : visited)
      if (val >= p.first)
        ++answer;
    
    cout << answer - 1 << '\n';
  }
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}