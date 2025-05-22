#include <iostream>
#include <array>
#include <queue>
#include <utility>
using namespace std;

int n, k, s, x, y;
array<array<int, 201>, 201> map;
array<array<bool, 201>, 201> visited;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> k;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      cin >> map[i][j];

  cin >> s >> x >> y;
}

void BreadthFirstSearch() {
  queue<pair<int, int>> q;
  for (int virus = 1; virus <= k; ++virus)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        if (map[i][j] == virus) {
          q.push({ i, j });
          visited[i][j] = true;
        }
  q.push({ -1, -1 });

  int step = 0;
  while (step < s) {
    pair<int, int> p = q.front();
    int row = p.first;
    int col = p.second;
    q.pop();

    if (row == -1 && col == -1) {
      ++step;
      q.push({ -1, -1 });
      continue;
    }

    array<int, 4> move_rows = { 1, 0, -1, 0 };
    array<int, 4> move_cols = { 0, 1, 0, -1 };
    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (next_row <= 0 || next_col <= 0 || next_row > n || next_col > n)
        continue;
      
      if (visited[next_row][next_col])
        continue;
      
      q.push({ next_row, next_col });
      map[next_row][next_col] = map[row][col];
      visited[next_row][next_col] = true;
    }
  }
}

void Solve() {
  BreadthFirstSearch();
  cout << map[x][y] << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}