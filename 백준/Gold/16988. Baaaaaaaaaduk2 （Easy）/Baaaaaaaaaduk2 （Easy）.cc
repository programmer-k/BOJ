#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> map(22, vector<int>(22));
int answer;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      cin >> map[i][j];
}

int BreadthFirstSearch(pair<int, int> start, vector<vector<bool>>& visited) {
  bool is_blocked = true;
  int count = 0;
  queue<pair<int, int>> q;
  q.push(start);
  visited[start.first][start.second] = true;

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int row = p.first;
    int col = p.second;
    q.pop();
    ++count;

    vector<int> move_rows = {1, 0, -1, 0};
    vector<int> move_cols = {0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (map[next_row][next_col] == 0)
        is_blocked = false;

      if (map[next_row][next_col] != 2)
        continue;

      if (visited[next_row][next_col])
        continue;

      q.push({next_row, next_col});
      visited[next_row][next_col] = true;
    }
  }

  return is_blocked ? count : 0;
}

void PaintAndCountKills(int r1, int c1, int r2, int c2) {
  if (r1 == r2 && c1 == c2)
    return;

  map[r1][c1] = map[r2][c2] = 1;

  int kills = 0;
  vector<vector<bool>> visited(22, vector<bool>(22));
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (map[i][j] == 2 && !visited[i][j])
        kills += BreadthFirstSearch({i, j}, visited);
  answer = max(answer, kills);

  map[r1][c1] = map[r2][c2] = 0;
}

void Solve() {
  for (int i = 0; i < 22; ++i) {
    map[i][0] = 3;
    map[0][i] = 3;
    map[n + 1][i] = 3;
    map[i][m + 1] = 3;
  }

  for (int rock1_row = 1; rock1_row <= n; ++rock1_row)
    for (int rock1_col = 1; rock1_col <= m; ++rock1_col)
      for (int rock2_row = 1; rock2_row <= n; ++rock2_row)
        for (int rock2_col = 1; rock2_col <= m; ++rock2_col)
          if (map[rock1_row][rock1_col] == 0 && map[rock2_row][rock2_col] == 0)
            PaintAndCountKills(rock1_row, rock1_col, rock2_row, rock2_col);

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
