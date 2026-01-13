#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

int r, c, n;
char cave[100][100];
int heights[100];
int visited[100][100];
int move_rows[4] = {1, 0, -1, 0};
int move_cols[4] = {0, 1, 0, -1};

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> r >> c;

  for (int i = 0; i < r; ++i)
    for (int j = 0; j < c; ++j)
      cin >> cave[i][j];

  cin >> n;

  for (int i = 0; i < n; ++i)
    cin >> heights[i];
}

void Paint(vector<pair<int, int>>& coordinates, int down, char ch) {
  for (const pair<int, int>& p : coordinates)
    cave[p.first + down][p.second] = ch;
}

bool IsMoveDown(vector<pair<int, int>>& coordinates, int down) {
  for (const pair<int, int>& p : coordinates)
    if (p.first + down >= r || cave[p.first + down][p.second] == 'x')
      return false;

  return true;
}

bool BreadthFirstSearch(int start_row, int start_col) {
  bool reached_floor = false;
  queue<pair<int, int>> q;
  vector<pair<int, int>> coordinates;
  memset(visited, -1, sizeof(visited));

  if (start_row < 0 || start_col < 0 || start_row >= r || start_col >= c)
    return false;

  if (cave[start_row][start_col] == '.')
    return false;

  q.push({start_row, start_col});
  visited[start_row][start_col] = 0;

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int row = p.first;
    int col = p.second;
    q.pop();

    coordinates.push_back({row, col});

    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (next_row >= r) {
        reached_floor = true;
        continue;
      }

      if (next_row < 0 || next_col < 0 || next_col >= c)
        continue;

      if (cave[next_row][next_col] == '.')
        continue;

      if (visited[next_row][next_col] != -1)
        continue;

      q.push({next_row, next_col});
      visited[next_row][next_col] = visited[row][col] + 1;
    }
  }

  if (reached_floor)
    return false;

  Paint(coordinates, 0, '.');

  int down = 1;
  while (IsMoveDown(coordinates, down)) {
    ++down;
  }

  Paint(coordinates, down - 1, 'x');
  return true;
}

void ThrowStick(int index, int row_index) {
  int col_index = index % 2 == 0 ? 0 : c - 1;
  int increment = index % 2 == 0 ? 1 : -1;

  while (col_index >= 0 && col_index < c && cave[row_index][col_index] == '.')
    col_index += increment;

  // The stick does not encounter a mineral.
  if (col_index < 0 || col_index >= c)
    return;

  // Destroy the mineral.
  cave[row_index][col_index] = '.';

  // Check whether there is a new floating cluster.
  for (int i = 0; i < 4; ++i)
    if (BreadthFirstSearch(row_index + move_rows[i], col_index + move_cols[i]))
      break;
}

void Solve() {
  for (int i = 0; i < n; ++i)
    ThrowStick(i, r - heights[i]);

  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j)
      cout << cave[i][j];
    cout << '\n';
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
