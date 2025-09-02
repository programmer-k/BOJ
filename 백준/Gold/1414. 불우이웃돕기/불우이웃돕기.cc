#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

class UnionFind {
 public:
  UnionFind(int size) : parents_(size) {
    for (int i = 0; i < size; ++i)
      parents_[i] = i;
  }

  int Find(int x) {
    if (x == parents_[x])
      return x;
    return parents_[x] = Find(parents_[x]);
  }

  bool Union(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y)
      return false;

    parents_[y] = x;
    return true;
  }

 private:
  vector<int> parents_;
};

struct Edge {
  int from;
  int to;
  int weight;

  bool operator<(const Edge& rhs) {
    return tie(weight, from, to) < tie(rhs.weight, rhs.from, rhs.to);
  }
};

int n;
vector<vector<char>> map(50, vector<char>(50));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> map[i][j];
}

int CharToInt(char ch) {
  if (ch >= 'a' && ch <= 'z')
    return ch - 'a' + 1;
  return ch - 'A' + 27;
}

int Kruskal(vector<Edge>& edges) {
  UnionFind union_find(n);
  sort(edges.begin(), edges.end());

  int total = 0;
  int count = 0;
  for (const Edge& edge : edges) {
    if (union_find.Union(edge.from, edge.to)) {
      total += edge.weight;
      ++count;
    }
  }

  if (count == n - 1)
    return total;
  return -1;
}

void Solve() {
  int total = 0;
  vector<Edge> edges;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (map[i][j] != '0') {
        edges.push_back({i, j, CharToInt(map[i][j])});
        total += CharToInt(map[i][j]);
      }

  int mst = Kruskal(edges);
  cout << (mst == -1 ? mst : total - mst) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
