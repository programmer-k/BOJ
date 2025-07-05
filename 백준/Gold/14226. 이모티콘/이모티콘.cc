#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
#include <limits>
using namespace std;

int s;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> s;
}

void Dijkstra() {
  const int kIntMax = numeric_limits<int>::max();
  vector<int> dists(2'001, kIntMax);
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({ 0, 1 });
  dists[0] = dists[1] = 0;

  while (!pq.empty()) {
    pair<int, int> p = pq.top();
    int curr_node = p.second;
    int curr_dist = p.first;
    pq.pop();

    if (curr_dist > dists[curr_node])
      continue;

    for (int i = 2, next_node = curr_node * i; next_node <= 2'000; ++i, next_node += curr_node) {
      int next_dist = curr_dist + i;

      if (next_dist < dists[next_node]) {
        pq.push({ next_dist, next_node });
        dists[next_node] = next_dist;
      }
    }

    if (curr_dist + 1 < dists[curr_node - 1]) {
      pq.push({ curr_dist + 1, curr_node - 1 });
      dists[curr_node - 1] = curr_dist + 1;
    }
  }

  cout << dists[s] << '\n';
}

void Solve() {
  Dijkstra();
}

int main() {
  GetInput();
  Solve();
  return 0;
}
