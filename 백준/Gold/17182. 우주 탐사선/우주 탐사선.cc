#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

const int kIntMax = numeric_limits<int>::max();
int n, k;
vector<vector<int>> matrix(10, vector<int>(10));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> matrix[i][j];
}

void Dijkstra(int start, vector<int>& dists) {
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  pq.push({0, start});
  dists[start] = 0;

  while (!pq.empty()) {
    pair<int, int> p = pq.top();
    int curr_dist = p.first;
    int curr_node = p.second;
    pq.pop();

    if (curr_dist > dists[curr_node])
      continue;

    for (int next_node = 0; next_node < n; ++next_node) {
      int next_dist = curr_dist + matrix[curr_node][next_node];

      if (next_dist < dists[next_node]) {
        pq.push({next_dist, next_node});
        dists[next_node] = next_dist;
      }
    }
  }
}

void Solve() {
  vector<vector<int>> dists(n, vector<int>(n, kIntMax));
  for (int i = 0; i < n; ++i)
    Dijkstra(i, dists[i]);

  vector<int> vec;
  for (int i = 0; i < n; ++i)
    if (i != k)
      vec.push_back(i);

  int min_time = kIntMax;
  do {
    int total = dists[k][vec[0]];
    for (int i = 0; i < ssize(vec) - 1; ++i)
      total += dists[vec[i]][vec[i + 1]];
    min_time = min(min_time, total);
  } while (next_permutation(vec.begin(), vec.end()));

  cout << min_time << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
