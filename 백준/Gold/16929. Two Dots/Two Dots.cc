#include <iostream>
#include <vector>
using namespace std;

struct UnionFind {
  vector<int> parents;

  UnionFind(int size) : parents(size) {
    for (int i = 0; i < ssize(parents); ++i)
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
vector<vector<char>> board;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  board.resize(n);
  for (int i = 0; i < n; ++i) {
    board[i].resize(m);
    for (int j = 0; j < m; ++j)
      cin >> board[i][j];
  }
}

int GetNodeNumber(int i, int j) {
  return i * m + j;
}

void Solve() {
  bool is_cycle = false;
  UnionFind union_find(n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i < n - 1 && board[i][j] == board[i + 1][j] && !union_find.Union(GetNodeNumber(i, j), GetNodeNumber(i + 1, j)))
        is_cycle = true;

      if (j < m - 1 && board[i][j] == board[i][j + 1] && !union_find.Union(GetNodeNumber(i, j), GetNodeNumber(i, j + 1)))
        is_cycle = true;
    }
  }

  if (is_cycle)
    cout << "Yes\n";
  else
    cout << "No\n";
}

int main() {
  GetInput();
  Solve();
  return 0;
}
