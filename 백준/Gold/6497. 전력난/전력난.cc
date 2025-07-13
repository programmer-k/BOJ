#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

struct UnionFind {
  vector<int> parents;

  UnionFind() : parents(200'000) {
    for (int i = 0; i < 200'000; ++i)
      parents[i] = i;
  }

  int Find(int x) {
    if (x == parents[x])
      return x;
    return parents[x] = Find(parents[x]);
  }

  bool Union(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y)
      return false;
    
    parents[y] = x;
    return true;
  }
};

struct Edge {
  int node1;
  int node2;
  int dist;

  bool operator<(const Edge& rhs) const {
    return tie(this->dist, node1, node2) < tie(rhs.dist, rhs.node1, rhs.node2);
  }
};

int m, n;
vector<Edge> edges;

bool GetInput1() {
  cin >> m >> n;

  if (n == 0 && m == 0)
    return false;
  return true;
}

void GetInput2() {
  edges.clear();
  for (int i = 0; i < n; ++i) {
    int x, y, z;
    cin >> x >> y >> z;
    edges.push_back({ x, y, z });
  }
}

int KruskalAlgorithm() {
  sort(edges.begin(), edges.end());

  int total = 0;
  UnionFind union_find;
  for (const Edge& edge : edges)
    if (union_find.Union(edge.node1, edge.node2))
      total += edge.dist;

  return total;
}

void Solve() {
  int total_distance = 0;
  for (const Edge& edge : edges)
    total_distance += edge.dist;

  cout << total_distance - KruskalAlgorithm() << '\n';
}

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  while (GetInput1()) {
    GetInput2();
    Solve();
  }
  return 0;
}