#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

struct Fish {
  int row;
  int col;
  int direction;
};

int m, s;
Fish fishes[10];
pair<int, int> shark;
vector<int> grid[5][5];
vector<int> grid_copy[5][5];
vector<int> grid_new[5][5];
int scents[5][5];

int fish_move_rows[8] = {1, 0, -1, -1, -1, 0, 1, 1};
int fish_move_cols[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int shark_move_rows[4] = {-1, 0, 1, 0};
int shark_move_cols[4] = {0, -1, 0, 1};

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> m >> s;

  for (int i = 0; i < m; ++i)
    cin >> fishes[i].row >> fishes[i].col >> fishes[i].direction;

  cin >> shark.first >> shark.second;
}

void RegisterFishes() {
  for (int i = 0; i < m; ++i)
    grid[fishes[i].row][fishes[i].col].push_back(fishes[i].direction);
}

void PrepareCopyMagic() {
  for (int i = 1; i <= 4; ++i)
    for (int j = 1; j <= 4; ++j)
      grid_copy[i][j] = grid[i][j];
}

void MoveFish(int row, int col, int direction) {
  for (int i = 8; i > 0; --i) {
    int next_row = row + fish_move_rows[(direction + i) % 8];
    int next_col = col + fish_move_cols[(direction + i) % 8];

    if (next_row <= 0 || next_col <= 0 || next_row >= 5 || next_col >= 5)
      continue;

    if (next_row == shark.first && next_col == shark.second)
      continue;

    if (scents[next_row][next_col] > 0)
      continue;

    grid_new[next_row][next_col].push_back((direction + i) % 8);
    return;
  }

  grid_new[row][col].push_back(direction % 8);
}

void MoveFishes() {
  for (int i = 1; i <= 4; ++i)
    for (int j = 1; j <= 4; ++j)
      grid_new[i][j].clear();

  for (int i = 1; i <= 4; ++i)
    for (int j = 1; j <= 4; ++j)
      for (int k = 0; k < ssize(grid[i][j]); ++k)
        MoveFish(i, j, grid[i][j][k]);

  for (int i = 1; i <= 4; ++i)
    for (int j = 1; j <= 4; ++j)
      grid[i][j] = grid_new[i][j];
}

void MoveShark() {
  pair<int, int> next_shark;
  set<pair<int, int>> positions;
  int max_total = -1;
  int min_move_path = -1;

  for (int i = 0; i < 4; ++i) {
    int next_row1 = shark.first + shark_move_rows[i];
    int next_col1 = shark.second + shark_move_cols[i];

    if (next_row1 <= 0 || next_col1 <= 0 || next_row1 >= 5 || next_col1 >= 5)
      continue;

    for (int j = 0; j < 4; ++j) {
      int next_row2 = next_row1 + shark_move_rows[j];
      int next_col2 = next_col1 + shark_move_cols[j];

      if (next_row2 <= 0 || next_col2 <= 0 || next_row2 >= 5 || next_col2 >= 5)
        continue;

      for (int k = 0; k < 4; ++k) {
        int next_row3 = next_row2 + shark_move_rows[k];
        int next_col3 = next_col2 + shark_move_cols[k];

        if (next_row3 <= 0 || next_col3 <= 0 || next_row3 >= 5 ||
            next_col3 >= 5)
          continue;

        set<pair<int, int>> s;
        s.insert({next_row1, next_col1});
        s.insert({next_row2, next_col2});
        s.insert({next_row3, next_col3});

        int total = 0;
        for (const pair<int, int>& p : s)
          total += ssize(grid[p.first][p.second]);

        if (total > max_total) {
          max_total = total;
          min_move_path = (i + 1) * 100 + (j + 1) * 10 + (k + 1);
          positions = s;
          next_shark = make_pair(next_row3, next_col3);
        } else if (total == max_total) {
          int move_path = (i + 1) * 100 + (j + 1) * 10 + (k + 1);
          if (move_path < min_move_path) {
            min_move_path = move_path;
            positions = s;
            next_shark = make_pair(next_row3, next_col3);
          }
        }
      }
    }
  }

  for (const pair<int, int>& p : positions) {
    if (ssize(grid[p.first][p.second]) > 0) {
      grid[p.first][p.second].clear();
      scents[p.first][p.second] = 3;
    }
  }

  shark = next_shark;
}

void UpdateFishScent() {
  for (int i = 1; i <= 4; ++i)
    for (int j = 1; j <= 4; ++j)
      if (scents[i][j] > 0)
        --scents[i][j];
}

void ApplyCopyMagic() {
  for (int i = 1; i <= 4; ++i)
    for (int j = 1; j <= 4; ++j)
      for (int k = 0; k < ssize(grid_copy[i][j]); ++k)
        grid[i][j].push_back(grid_copy[i][j][k]);
}

int CountAllFishes() {
  int total = 0;
  for (int i = 1; i <= 4; ++i)
    for (int j = 1; j <= 4; ++j)
      total += ssize(grid[i][j]);
  return total;
}

void Solve() {
  RegisterFishes();

  for (int i = 0; i < s; ++i) {
    PrepareCopyMagic();
    MoveFishes();
    MoveShark();
    UpdateFishScent();
    ApplyCopyMagic();
  }

  cout << CountAllFishes() << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
