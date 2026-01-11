#include <iostream>
#include <utility>
using namespace std;

int n, m;
char board[10][10];
pair<int, int> hole;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> board[i][j];
}

pair<int, int> Find(char val) {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (board[i][j] == val)
        return {i, j};
  return {-1, -1};
}

bool IsWallOrHole(int row, int col) {
  return board[row][col] == '#' || board[row][col] == 'O';
}

pair<int, int> MoveBall(pair<int, int> ball, int direction) {
  int move_rows[4] = {1, 0, -1, 0};
  int move_cols[4] = {0, 1, 0, -1};

  int next_row = ball.first;
  int next_col = ball.second;

  while (!IsWallOrHole(next_row, next_col)) {
    next_row += move_rows[direction];
    next_col += move_cols[direction];
  }

  if (board[next_row][next_col] == 'O')
    return {next_row, next_col};
  else
    return {next_row - move_rows[direction], next_col - move_cols[direction]};
}

void HandleDuplicate(pair<int, int> red, pair<int, int> blue,
                     pair<int, int>& next_red, pair<int, int>& next_blue,
                     int direction) {
  if (next_red == next_blue && board[next_red.first][next_red.second] != 'O') {
    if (red < blue && direction == 0)
      --next_red.first;
    else if (red < blue && direction == 1)
      --next_red.second;
    else if (red < blue && direction == 2)
      ++next_blue.first;
    else if (red < blue && direction == 3)
      ++next_blue.second;
    else if (red > blue && direction == 0)
      --next_blue.first;
    else if (red > blue && direction == 1)
      --next_blue.second;
    else if (red > blue && direction == 2)
      ++next_red.first;
    else if (red > blue && direction == 3)
      ++next_red.second;
  }
}

bool DepthFirstSearch(int step, pair<int, int> red, pair<int, int> blue) {
  if (step > 10)
    return false;

  bool found = false;
  for (int i = 0; i < 4; ++i) {
    pair<int, int> next_red = MoveBall(red, i);
    pair<int, int> next_blue = MoveBall(blue, i);
    HandleDuplicate(red, blue, next_red, next_blue, i);

    bool found_solution = board[next_red.first][next_red.second] == 'O' &&
                          board[next_blue.first][next_blue.second] != 'O';
    found = found || found_solution ||
            DepthFirstSearch(step + 1, next_red, next_blue);
  }

  return found;
}

void Solve() {
  hole = Find('O');
  pair<int, int> red_ball = Find('R');
  pair<int, int> blue_ball = Find('B');
  cout << DepthFirstSearch(1, red_ball, blue_ball) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
