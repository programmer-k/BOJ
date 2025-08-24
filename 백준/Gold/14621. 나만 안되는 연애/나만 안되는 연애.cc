#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

class UnionFind {
 public:
  UnionFind(int n) : parents(n + 1) {
    for (int i = 1; i <= n; ++i)
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
  int u;
  int v;
  int d;

  bool operator<(const Edge& rhs) {
    return tie(d, u, v) < tie(rhs.d, rhs.u, rhs.v);
  }
};

int n, m;
vector<char> schools(1'001);
vector<Edge> edges;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  for (int i = 1; i <= n; ++i)
    cin >> schools[i];

  for (int i = 0; i < m; ++i) {
    int u, v, d;
    cin >> u >> v >> d;
    edges.push_back({ u, v, d });
  }
}

int Kruskal() {
  sort(edges.begin(), edges.end());

  int count = 0;
  int total = 0;
  UnionFind union_find(n);
  for (const Edge& edge : edges) {
    if (schools[edge.u] != schools[edge.v] && union_find.Union(edge.u, edge.v)) {
      total += edge.d;
      ++count;
    }
  }
  
  return count == n - 1 ? total : -1;
}

void Solve() {
  cout << Kruskal() << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
