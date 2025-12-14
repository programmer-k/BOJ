#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

struct Data {
  int stop_over;
  int max_fuel;
  int node;

  bool operator<(const Data& rhs) const {
    return tie(max_fuel, stop_over, node) <
           tie(rhs.max_fuel, rhs.stop_over, rhs.node);
  }

  bool operator>(const Data& rhs) const {
    return rhs < *this;
  }
};

const int kIntMax = numeric_limits<int>::max();

int n, k;
vector<pair<int, int>> coordinates;
vector<vector<pair<int, int>>> edges;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> k;

  coordinates.resize(n + 2);
  for (int i = 1; i <= n; ++i)
    cin >> coordinates[i].first >> coordinates[i].second;
  coordinates[n + 1].first = coordinates[n + 1].second = 10'000;
}

vector<vector<pair<int, int>>> CreateEdges() {
  vector<vector<pair<int, int>>> edges(n + 2);
  for (int i = 0; i <= n + 1; ++i) {
    for (int j = i + 1; j <= n + 1; ++j) {
      int x_diff = coordinates[i].first - coordinates[j].first;
      int y_diff = coordinates[i].second - coordinates[j].second;
      double dist = sqrt(x_diff * x_diff + y_diff * y_diff);
      int fuel = ceil(dist / 10.0);

      edges[i].push_back({j, fuel});
      edges[j].push_back({i, fuel});
    }
  }

  return edges;
}

int Dijkstra(const vector<vector<pair<int, int>>>& edges) {
  priority_queue<Data, vector<Data>, greater<Data>> pq;
  vector<vector<int>> dists(n + 2, vector<int>(k + 2, kIntMax));
  pq.push({0, 0, 0});
  dists[0][0] = 0;

  while (!pq.empty()) {
    Data data = pq.top();
    int stop_over = data.stop_over;
    int max_fuel = data.max_fuel;
    int curr_node = data.node;
    pq.pop();

    if (max_fuel > dists[curr_node][stop_over])
      continue;

    if (curr_node == n + 1)
      return max_fuel;

    if (stop_over == k + 1)
      continue;

    for (const pair<int, int>& next : edges[curr_node]) {
      int next_stop_over = stop_over + 1;
      int next_max_fuel = max(max_fuel, next.second);
      int next_node = next.first;

      if (next_max_fuel < dists[next_node][next_stop_over]) {
        pq.push({next_stop_over, next_max_fuel, next_node});
        dists[next_node][next_stop_over] = next_max_fuel;
      }
    }
  }

  return -1;
}

void Solve() {
  cout << Dijkstra(CreateEdges()) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
