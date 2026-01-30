#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

struct Data {
  int node;
  int dist;
  int count;

  bool operator<(const Data& rhs) const {
    return tie(dist, node, count) < tie(rhs.dist, rhs.node, rhs.count);
  }

  bool operator>(const Data& rhs) const {
    return rhs < *this;
  }
};

const int kIntMax = numeric_limits<int>::max();

int n, m;
vector<pair<int, int>> edges[4'001];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  for (int i = 0; i < m; ++i) {
    int a, b, d;
    cin >> a >> b >> d;
    edges[a].push_back({b, d});
    edges[b].push_back({a, d});
  }
}

vector<int> DijkstraFox() {
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  vector<int> dists(n + 1, kIntMax);
  pq.push({0, 1});
  dists[1] = 0;

  while (!pq.empty()) {
    pair<int, int> p = pq.top();
    int curr_dist = p.first;
    int curr_node = p.second;
    pq.pop();

    if (curr_dist > dists[curr_node])
      continue;

    for (const pair<int, int>& next : edges[curr_node]) {
      int next_node = next.first;
      int next_step = next.second;
      int next_dist = curr_dist + next_step;

      if (next_dist < dists[next_node]) {
        pq.push({next_dist, next_node});
        dists[next_node] = next_dist;
      }
    }
  }

  return dists;
}

vector<int> DijkstraWolf() {
  priority_queue<Data, vector<Data>, greater<Data>> pq;
  vector<vector<int>> dists(2, vector<int>(n + 1, kIntMax));
  pq.push({1, 0, 0});
  dists[0][1] = 0;

  while (!pq.empty()) {
    Data data = pq.top();
    int curr_dist = data.dist;
    int curr_node = data.node;
    int curr_count = data.count;
    pq.pop();

    if (curr_dist > dists[curr_count % 2][curr_node])
      continue;

    for (const pair<int, int>& next : edges[curr_node]) {
      int next_node = next.first;
      int next_step = next.second;
      int next_dist = curr_count % 2 == 0 ? curr_dist + next_step
                                          : curr_dist + next_step * 4;

      if (next_dist < dists[(curr_count + 1) % 2][next_node]) {
        pq.push({next_node, next_dist, curr_count + 1});
        dists[(curr_count + 1) % 2][next_node] = next_dist;
      }
    }
  }

  vector<int> min_dists(n + 1);
  for (int i = 0; i < ssize(dists[0]); ++i)
    min_dists[i] = min(dists[0][i], dists[1][i]);
  return min_dists;
}

void Solve() {
  vector<int> fox_dists = DijkstraFox();
  vector<int> wolf_dists = DijkstraWolf();

  int answer = 0;
  for (int i = 1; i <= n; ++i)
    if (fox_dists[i] != kIntMax && fox_dists[i] * 2 < wolf_dists[i])
      ++answer;

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
