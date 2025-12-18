#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

struct Data {
  pair<int, int> red;
  pair<int, int> blue;
};

int n, m;
vector<vector<char>> board(10, vector<char>(10));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> board[i][j];
}

pair<int, int> Find(char ch) {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (board[i][j] == ch)
        return {i, j};
  return {-1, -1};
}

int GetIndex(const pair<int, int>& pos) {
  return pos.first * m + pos.second;
}

pair<int, int> Move(pair<int, int> pos, int direction) {
  vector<int> move_rows = {-1, 1, 0, 0};
  vector<int> move_cols = {0, 0, -1, 1};

  int next_row = pos.first + move_rows[direction];
  int next_col = pos.second + move_cols[direction];

  if (next_row < 0 || next_col < 0 || next_row >= n || next_col >= m)
    return pos;

  if (board[next_row][next_col] == '#')
    return pos;

  return {next_row, next_col};
}

int BreadthFirstSearch(pair<int, int> red_start, pair<int, int> blue_start,
                       pair<int, int> hole) {
  queue<Data> q;
  vector<vector<int>> visited(n * m, vector<int>(n * m, -1));
  q.push({red_start, blue_start});
  visited[GetIndex(red_start)][GetIndex(blue_start)] = 0;

  while (!q.empty()) {
    Data data = q.front();
    pair<int, int> red = data.red;
    pair<int, int> blue = data.blue;
    q.pop();

    if (red == hole && blue != hole)
      return visited[GetIndex(red)][GetIndex(blue)];

    if (blue == hole)
      continue;

    if (visited[GetIndex(red)][GetIndex(blue)] == 11)
      return -1;

    for (int i = 0; i < 4; ++i) {
      pair<int, int> next_red(red);
      pair<int, int> next_blue(blue);

      bool is_red_move;
      bool is_blue_move;
      pair<int, int> next_step_red;
      pair<int, int> next_step_blue;
      do {
        next_step_red = Move(next_red, i);
        next_step_blue = Move(next_blue, i);
        is_red_move = next_red != next_step_red;
        is_blue_move = next_blue != next_step_blue;

        if (next_step_red == next_step_blue)
          break;

        next_red = next_step_red;
        next_blue = next_step_blue;

        if (next_red == hole || next_blue == hole)
          break;
      } while (is_red_move || is_blue_move);

      if (next_red == hole) {
        do {
          next_step_blue = Move(next_blue, i);
          is_blue_move = next_blue != next_step_blue;
          next_blue = next_step_blue;

          if (next_step_blue == hole)
            break;
        } while (is_blue_move);
      }

      if (visited[GetIndex(next_red)][GetIndex(next_blue)] == -1) {
        q.push({next_red, next_blue});
        visited[GetIndex(next_red)][GetIndex(next_blue)] =
            visited[GetIndex(red)][GetIndex(blue)] + 1;
      }
    }
  }

  return -1;
}

void Solve() {
  pair<int, int> red = Find('R');
  pair<int, int> blue = Find('B');
  pair<int, int> hole = Find('O');

  cout << BreadthFirstSearch(red, blue, hole) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
