#include <deque>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>
using namespace std;

const int kIntMax = numeric_limits<int>::max();
int n, m, k;
vector<vector<pair<int, int>>> edges;
vector<pair<int, int>> questions;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  edges.resize(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v, b;
    cin >> u >> v >> b;
    edges[u].push_back({v, 0});

    if (b == 0)
      edges[v].push_back({u, 1});
    else
      edges[v].push_back({u, 0});
  }

  cin >> k;

  questions.resize(k);
  for (int i = 0; i < k; ++i)
    cin >> questions[i].first >> questions[i].second;
}

void ZeroOneBreadthFirstSearch(int start, vector<int>& dists) {
  deque<int> deq;
  deq.push_back(start);
  dists[start] = 0;

  while (!deq.empty()) {
    int node = deq.front();
    deq.pop_front();

    for (const pair<int, int>& next : edges[node]) {
      if (dists[node] + next.second < dists[next.first]) {
        if (next.second == 0) {
          deq.push_front(next.first);
        } else {
          deq.push_back(next.first);
        }
        dists[next.first] = dists[node] + next.second;
      }
    }
  }
}

void Solve() {
  vector<vector<int>> dists(n + 1, vector<int>(n + 1, kIntMax));
  for (int i = 1; i <= n; ++i)
    ZeroOneBreadthFirstSearch(i, dists[i]);

  for (const pair<int, int>& question : questions)
    cout << dists[question.first][question.second] << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
