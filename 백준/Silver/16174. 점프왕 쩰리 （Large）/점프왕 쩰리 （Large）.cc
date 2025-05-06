#include <iostream>
#include <array>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

int n;
array<array<int, 64>, 64> map;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> map[i][j];
}

bool BreadthFirstSearch() {
  queue<pair<int, int>> q;
  vector<vector<bool>> visited(n, vector<bool>(n, false));
  q.push({ 0, 0 });
  visited[0][0] = true;

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int row = p.first;
    int col = p.second;
    q.pop();

    if (map[row][col] == -1)
      return true;

    array<int, 2> move_rows = { 1, 0 };
    array<int, 2> move_cols = { 0, 1 };
    for (int i = 0; i < 2; ++i) {
      int next_row = row + move_rows[i] * map[row][col];
      int next_col = col + move_cols[i] * map[row][col];

      if (next_row >= n || next_col >= n)
        continue;
      
      vector<bool>::reference visit = visited[next_row][next_col];
      if (visit)
        continue;
      
      q.push({ next_row, next_col });
      visit = true;
    }
  }

  return false;
}

void Solve() {
  if (BreadthFirstSearch())
    cout << "HaruHaru\n";
  else
    cout << "Hing\n";
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}