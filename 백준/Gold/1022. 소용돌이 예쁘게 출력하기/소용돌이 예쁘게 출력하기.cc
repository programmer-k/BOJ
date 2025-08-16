#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

int r1, c1, r2, c2;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> r1 >> c1 >> r2 >> c2;
}

bool IsInRange(int row, int col, int& num) {
  ++num;
  if (row >= 0 && row < r2 && col >= 0 && col < c2)
    return true;
  return false;
}

void Paint(vector<vector<int>>& map, int row, int col, int num, int& count) {
  ++count;
  map[row][col] = num;
}

void Solve() {
  r2 -= r1;
  c2 -= c1;
  
  int num = 0;
  int row = -r1;
  int col = -c1;
  int count = 0;
  int steps = 1;
  int direction = 0;
  vector<vector<int>> map(++r2, vector<int>(++c2));
  vector<int> move_rows = { -1, 0, 1, 0 };
  vector<int> move_cols = { 0, -1, 0, 1 };

  if (IsInRange(row, col, num))
    Paint(map, row, col, num, count);
  if (IsInRange(row, ++col, num))
    Paint(map, row, col, num, count);
  
  while (count < r2 * c2) {
    for (int i = 0; i < 2; ++i) {
      for (int step = 0; step < steps; ++step) {
        row += move_rows[direction];
        col += move_cols[direction];

        if (IsInRange(row, col, num))
          Paint(map, row, col, num, count);
      }

      if (direction % 2 == 0)
        ++steps;
      direction = (direction + 1) % 4;
    }
  }

  int max_num_len = 0;
  for (int i = 0; i < r2; ++i)
    for (int j = 0; j < c2; ++j)
      max_num_len = max(max_num_len, static_cast<int>(to_string(map[i][j]).size()));

  for (int i = 0; i < r2; ++i) {
    for (int j = 0; j < c2; ++j) {
      cout << setw(max_num_len) << map[i][j] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
