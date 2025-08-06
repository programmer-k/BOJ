#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cstdint>
using namespace std;

struct UnionFind {
  vector<int> parents;

  UnionFind(int size) : parents(size) {
    for (int i = 1; i < size; ++i)
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
  int cost;

  Edge(int node1, int node2, int cost) {
    this->node1 = node1;
    this->node2 = node2;
    this->cost = cost;
  }

  bool operator<(const Edge& rhs) {
    return tie(cost, node1, node2) < tie(rhs.cost, rhs.node1, rhs.node2);
  }
};

int n;
vector<vector<int>> matrix;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  
  matrix.resize(n + 1);
  for (int i = 1; i <= n; ++i)
    matrix[i].resize(n + 1);

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      cin >> matrix[i][j];
}

int64_t Kruskal(vector<Edge>& edges) {
  sort(edges.begin(), edges.end());

  int64_t total = 0;
  UnionFind union_find(n + 1);
  for (const Edge& edge : edges)
    if (union_find.Union(edge.node1, edge.node2))
      total += edge.cost;

  return total;
}

void Solve() {
  vector<Edge> edges;
  
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j)
      edges.push_back({ i, j, matrix[i][j] });

  cout << Kruskal(edges) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
