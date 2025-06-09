#include <iostream>
#include <array>
#include <queue>
#include <utility>
#include <vector>
#include <limits>
using namespace std;

int n, m, t;
array<array<int, 100>, 100> map;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> t;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> map[i][j];
}

int BreadthFirstSearch() {
  int min_dist_with_item = numeric_limits<int>::max();
  queue<pair<int, int>> q;
  vector<vector<int>> visited(100, vector<int>(100, numeric_limits<int>::max()));
  q.push({ 0, 0 });
  visited[0][0] = 0;

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int row = p.first;
    int col = p.second;
    q.pop();

    if (map[row][col] == 2)
      min_dist_with_item = visited[row][col] + (n - 1 - row) + (m - 1 - col);

    array<int, 4> move_rows = { 0, 1, 0, -1 };
    array<int, 4> move_cols = { 1, 0, -1, 0 };
    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (next_row < 0 || next_col < 0 || next_row >= n || next_col >= m)
        continue;
      
      if (map[next_row][next_col] == 1)
        continue;

      int& visit = visited[next_row][next_col];
      if (visit != numeric_limits<int>::max())
        continue;
      
      q.push({ next_row, next_col });
      visit = visited[row][col] + 1;
    }
  }

  return min(visited[n - 1][m - 1], min_dist_with_item);
}

void Solve() {
  int rescue_time = BreadthFirstSearch();
  if (rescue_time <= t)
    cout << rescue_time << '\n';
  else
    cout << "Fail\n";
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}