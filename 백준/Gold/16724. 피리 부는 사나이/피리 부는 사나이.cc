#include <iostream>
#include <vector>
#include <unordered_set>
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

int n, m;
vector<vector<char>> map(1'000, vector<char>(1'000));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> map[i][j];
}

int GetIndex(int row, int col) {
  return row * m + col;
}

void Solve() {
  UnionFind union_find(n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char val = map[i][j];

      if (val == 'U')
        union_find.Union(GetIndex(i, j), GetIndex(i - 1, j));
      else if (val == 'D')
        union_find.Union(GetIndex(i, j), GetIndex(i + 1, j));
      else if (val == 'L')
        union_find.Union(GetIndex(i, j), GetIndex(i, j - 1));
      else
        union_find.Union(GetIndex(i, j), GetIndex(i, j + 1));
    }
  }

  unordered_set<int> s;
  for (int i = 0; i < n * m; ++i)
    s.insert(union_find.Find(i));

  cout << s.size() << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}