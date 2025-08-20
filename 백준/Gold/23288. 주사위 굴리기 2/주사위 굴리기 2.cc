#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int n, m, k;
vector<vector<int>> map(20, vector<int>(20));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> k;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> map[i][j];
}

void DepthFirstSearch(int row, int col, int& count, vector<vector<int>>& visited, vector<pair<int, int>>& coordinates) {
  coordinates.push_back({ row, col });
  visited[row][col] = 0;
  ++count;

  vector<int> move_rows = { 1, 0, -1, 0 };
  vector<int> move_cols = { 0, 1, 0, -1 };
  for (int i = 0; i < 4; ++i) {
    int next_row = row + move_rows[i];
    int next_col = col + move_cols[i];

    if (next_row < 0 || next_col < 0 || next_row >= n || next_col >= m)
      continue;
    
    if (visited[next_row][next_col] != -1)
      continue;
    
    if (map[row][col] != map[next_row][next_col])
      continue;

    DepthFirstSearch(next_row, next_col, count, visited, coordinates);
  }
}

void Paint(int row, int col, vector<vector<int>>& visited) {
  int count = 0;
  vector<pair<int, int>> coordinates;
  DepthFirstSearch(row, col, count, visited, coordinates);

  for (const pair<int, int>& coordinate : coordinates)
    visited[coordinate.first][coordinate.second] = count;
}

void MoveEast(int& row, int& col, vector<int>& dice) {
  vector<int> new_dice(6);
  new_dice[0] = dice[0];
  new_dice[1] = dice[5];
  new_dice[2] = dice[1];
  new_dice[3] = dice[2];
  new_dice[4] = dice[4];
  new_dice[5] = dice[3];
  
  dice = new_dice;
  ++col;
}

void MoveSouth(int& row, int& col, vector<int>& dice) {
  vector<int> new_dice(6);
  new_dice[0] = dice[5];
  new_dice[1] = dice[1];
  new_dice[2] = dice[0];
  new_dice[3] = dice[3];
  new_dice[4] = dice[2];
  new_dice[5] = dice[4];
  
  dice = new_dice;
  ++row;
}

void MoveWest(int& row, int& col, vector<int>& dice) {
  vector<int> new_dice(6);
  new_dice[0] = dice[0];
  new_dice[1] = dice[2];
  new_dice[2] = dice[3];
  new_dice[3] = dice[5];
  new_dice[4] = dice[4];
  new_dice[5] = dice[1];
  
  dice = new_dice;
  --col;
}

void MoveNorth(int& row, int& col, vector<int>& dice) {
  vector<int> new_dice(6);
  new_dice[0] = dice[2];
  new_dice[1] = dice[1];
  new_dice[2] = dice[4];
  new_dice[3] = dice[3];
  new_dice[4] = dice[5];
  new_dice[5] = dice[0];
  
  dice = new_dice;
  --row;
}

void ChangeDirection(int row, int col, int& direction) {
  vector<int> move_rows = { 0, 1, 0, -1 };
  vector<int> move_cols = { 1, 0, -1, 0 };

  int next_row = row + move_rows[direction];
  int next_col = col + move_cols[direction];

  if (next_row < 0 || next_col < 0 || next_row >= n || next_col >= m)
    direction = (direction + 2) % 4;
}

void MoveDice(int& row, int& col, int& direction, int& total_score, vector<int>& dice, vector<vector<int>>& visited) {
  ChangeDirection(row, col, direction);

  if (direction == 0)
    MoveEast(row, col, dice);
  else if (direction == 1)
    MoveSouth(row, col, dice);
  else if (direction == 2)
    MoveWest(row, col, dice);
  else
    MoveNorth(row, col, dice);

  total_score += map[row][col] * visited[row][col];

  int bottom = dice[5];
  if (bottom > map[row][col])
    direction = (direction + 1) % 4;
  else if (bottom < map[row][col])
    direction = (direction + 3) % 4;
}

void Solve() {
  vector<vector<int>> visited(n, vector<int>(m, -1));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (visited[i][j] == -1)
        Paint(i, j, visited);

  int row = 0;
  int col = 0;
  int direction = 0;
  int total_score = 0;
  vector<int> dice = { 2, 4, 1, 3, 5, 6 };

  for (int move = 0; move < k; ++move)
    MoveDice(row, col, direction, total_score, dice, visited);

  cout << total_score << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
