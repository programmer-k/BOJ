#include <cstring>
#include <iostream>
#include <utility>
#include <queue>
using namespace std;

struct Pos {
  int row;
  int col;
  int state;
};

int n, m;
char map[50][50];
int visited[50][50][1 << 6];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> map[i][j];
}

pair<int, int> GetStartPosition() {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (map[i][j] == '0')
        return {i, j};

  return {-1, -1};
}

int BreadthFirstSearch(pair<int, int> start) {
  queue<Pos> q;
  memset(visited, -1, sizeof(visited));
  q.push({start.first, start.second, 0});
  visited[start.first][start.second][0] = 0;

  while (!q.empty()) {
    Pos pos = q.front();
    int row = pos.row;
    int col = pos.col;
    int state = pos.state;
    q.pop();

    if (map[row][col] == '1')
      return visited[row][col][state];

    int move_rows[4] = {1, 0, -1, 0};
    int move_cols[4] = {0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (next_row < 0 || next_col < 0 || next_row >= n || next_col >= m)
        continue;

      char next_val = map[next_row][next_col];
      if (next_val == '#')
        continue;

      if (next_val >= 'A' && next_val <= 'F' && ((1 << (next_val - 'A')) & state) == 0)
        continue;

      int next_state = next_val >= 'a' && next_val <= 'f' ? state | (1 << (next_val - 'a')) : state;
      if (visited[next_row][next_col][next_state] != -1)
        continue;

      q.push({next_row, next_col, next_state});
      visited[next_row][next_col][next_state] = visited[row][col][state] + 1;
    }
  }

  return -1;
}

void Solve() {
  cout << BreadthFirstSearch(GetStartPosition()) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
