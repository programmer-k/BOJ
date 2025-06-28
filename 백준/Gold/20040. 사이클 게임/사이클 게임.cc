#include <iostream>
#include <array>
#include <utility>
using namespace std;

struct UnionFind {
  array<int, 500'000> parents;

  UnionFind() {
    for (int i = 0; i < 500'000; ++i)
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

int n, m;
array<pair<int, int>, 1'000'000> lines;
UnionFind union_find;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < m; ++i)
    cin >> lines[i].first >> lines[i].second;
}

void Solve() {
  int i;
  for (i = 0; i < m; ++i) {
    int point1 = lines[i].first;
    int point2 = lines[i].second;

    if (!union_find.Union(point1, point2))
      break;
  }

  if (i == m)
    cout << "0\n";
  else
    cout << i + 1 << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}