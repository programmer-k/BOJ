#include <iostream>
#include <array>
#include <vector>
using namespace std;

int n, m, r;
vector<vector<int>> arr(300, vector<int>(300));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> r;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> arr[i][j];
}

void Move(int& row, int& col, int index, vector<vector<int>>& vec) {
  array<int, 4> move_rows = { 1, 0, -1, 0 };
  array<int, 4> move_cols = { 0, 1, 0, -1 };

  while (true) {
    int next_row = row + move_rows[index];
    int next_col = col + move_cols[index];

    if (next_row >= n || next_col >= m || next_row < 0 || next_col < 0)
      break;

    if (vec[next_row][next_col] != -1)
      break;

    vec[next_row][next_col] = arr[row][col];
    
    row = next_row;
    col = next_col;
  }
}

void Rotate() {
  int loop = min(n, m) / 2;
  vector<vector<int>> rotated(n, vector<int>(m, -1));

  for (int i = 0; i < loop; ++i) {
    int row = i;
    int col = i;

    for (int j = 0; j < 4; ++j)
      Move(row, col, j, rotated);
  }

  arr = rotated;
}

void Solve() {
  for (int i = 0; i < r; ++i)
    Rotate();

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << arr[i][j] << ' ';
    }
    cout << '\n';
  }
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}