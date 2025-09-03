#include <algorithm>
#include <functional>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

class UnionFind {
 public:
  UnionFind(int size) : parents(size) {
    for (int i = 0; i < size; ++i)
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

 private:
  vector<int> parents;
};

struct Edge {
  int node1;
  int node2;
  int weight;

  bool operator<(const Edge& rhs) const {
    return tie(weight, node1, node2) < tie(rhs.weight, rhs.node1, rhs.node2);
  }

  bool operator>(const Edge& rhs) const {
    return rhs < *this;
  }
};

int n, m;
vector<Edge> edges;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < m + 1; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    c = c ? 0 : 1;
    edges.push_back({a, b, c});
  }
}

int Kruskal() {
  int count = 0;
  UnionFind union_find(n + 1);
  for (const Edge& edge : edges)
    if (union_find.Union(edge.node1, edge.node2))
      count += edge.weight;

  return count * count;
}

void Solve() {
  sort(edges.begin(), edges.end(), greater<Edge>());
  int maximum = Kruskal();

  sort(edges.begin(), edges.end());
  int minimum = Kruskal();
  cout << maximum - minimum << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
