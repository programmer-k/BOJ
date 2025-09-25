#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

class UnionFind {
 public:
  UnionFind(int n) : parents(n), sizes(n, 1) {
    for (int i = 0; i < n; ++i)
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

    if (sizes[x] < sizes[y])
      swap(x, y);

    parents[y] = x;
    sizes[x] += sizes[y];
    return true;
  }

  int GetSize(int x) {
    return sizes[x];
  }

 private:
  vector<int> parents, sizes;
};

int n, m;
vector<vector<int>> map(1'002, vector<int>(1'002));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      cin >> map[i][j];
}

int GetIndex(int row, int col) {
  return row * (m + 1) + col;
}

void Solve() {
  UnionFind union_find((n + 1) * (m + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (map[i][j] == 1 && map[i][j + 1] == 1)
        union_find.Union(GetIndex(i, j), GetIndex(i, j + 1));
      if (map[i][j] == 1 && map[i + 1][j] == 1)
        union_find.Union(GetIndex(i, j), GetIndex(i + 1, j));
    }
  }

  int max_size = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (map[i][j] == 0) {
        vector<int> move_rows = {1, 0, -1, 0};
        vector<int> move_cols = {0, 1, 0, -1};
        set<int> parents;

        for (int k = 0; k < 4; ++k) {
          int next_row = i + move_rows[k];
          int next_col = j + move_cols[k];

          if (map[next_row][next_col] == 1)
            parents.insert(union_find.Find(GetIndex(next_row, next_col)));
        }

        int total_size = 1;
        for (int parent : parents)
          total_size += union_find.GetSize(parent);
        max_size = max(max_size, total_size);
      }
    }
  }

  cout << max_size << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
