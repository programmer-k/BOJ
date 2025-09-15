#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<char>> map(501, vector<char>(501));

bool IsEdge(int index) {
  if (index < m + 2)
    return true;
  if (index % (m + 2) == 0)
    return true;
  if (index % (m + 2) == m + 1)
    return true;
  if (index >= (n + 1) * (m + 2))
    return true;
  return false;
}

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

    if (IsEdge(x))
      parents_[y] = x;
    else
      parents_[x] = y;
    return true;
  }

 private:
  vector<int> parents_;
};

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      cin >> map[i][j];
}

int GetIndex(int row, int col) {
  return row * (m + 2) + col;
}

void Solve() {
  UnionFind union_find((n + 2) * (m + 2));
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (map[i][j] == 'U')
        union_find.Union(GetIndex(i, j), GetIndex(i - 1, j));
      else if (map[i][j] == 'R')
        union_find.Union(GetIndex(i, j), GetIndex(i, j + 1));
      else if (map[i][j] == 'D')
        union_find.Union(GetIndex(i, j), GetIndex(i + 1, j));
      else
        union_find.Union(GetIndex(i, j), GetIndex(i, j - 1));

  int answer = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (IsEdge(union_find.Find(GetIndex(i, j))))
        ++answer;

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
