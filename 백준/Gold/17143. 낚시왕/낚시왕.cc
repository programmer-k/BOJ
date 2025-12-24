#include <iostream>
#include <vector>
using namespace std;

struct Shark {
  int speed;
  int direction;
  int size;

  bool operator==(const Shark& rhs) const {
    if (speed == rhs.speed && direction == rhs.direction && size == rhs.size)
      return true;
    return false;
  }

  bool operator!=(const Shark& rhs) const {
    return !(*this == rhs);
  }
};

int r, c, m;
vector<vector<Shark>> grid(101, vector<Shark>(101, Shark{-1, -1, -1}));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> r >> c >> m;

  for (int i = 0; i < m; ++i) {
    int r, c, s, d, z;
    cin >> r >> c >> s >> d >> z;
    grid[r][c] = {s, d - 1, z};
  }
}

int CatchShark(int col) {
  for (int row = 1; row <= r; ++row) {
    if (grid[row][col] != Shark{-1, -1, -1}) {
      int size = grid[row][col].size;
      grid[row][col] = {-1, -1, -1};
      return size;
    }
  }

  return 0;
}

bool IsOutOfBound(int row, int col, int speed, int direction) {
  vector<int> move_rows = {-1, 1, 0, 0};
  vector<int> move_cols = {0, 0, 1, -1};

  int next_row = row + move_rows[direction] * speed;
  int next_col = col + move_cols[direction] * speed;

  if (next_row <= 0 || next_col <= 0 || next_row > r || next_col > c)
    return true;

  return false;
}

int GetOppositeDirection(int direction) {
  if (direction == 0)
    return 1;
  else if (direction == 1)
    return 0;
  else if (direction == 2)
    return 3;
  else
    return 2;
}

void MoveShark(int row, int col, vector<vector<Shark>>& next_grid) {
  const Shark& shark = grid[row][col];
  int speed = shark.speed;
  int direction = shark.direction;
  int next_row = row;
  int next_col = col;

  while (IsOutOfBound(next_row, next_col, speed, direction)) {
    if (direction == 0) {
      speed -= next_row - 1;
      next_row = 1;
    } else if (direction == 1) {
      speed -= r - next_row;
      next_row = r;
    } else if (direction == 2) {
      speed -= c - next_col;
      next_col = c;
    } else {
      speed -= next_col - 1;
      next_col = 1;
    }

    direction = GetOppositeDirection(direction);
  }

  vector<int> move_rows = {-1, 1, 0, 0};
  vector<int> move_cols = {0, 0, 1, -1};

  next_row = next_row + move_rows[direction] * speed;
  next_col = next_col + move_cols[direction] * speed;

  if (grid[row][col].size > next_grid[next_row][next_col].size) {
    next_grid[next_row][next_col] = grid[row][col];
    next_grid[next_row][next_col].direction = direction;
  }
}

void MoveSharks() {
  vector<vector<Shark>> next_grid(101, vector<Shark>(101, Shark{-1, -1, -1}));
  for (int row = 1; row <= r; ++row) {
    for (int col = 1; col <= c; ++col) {
      if (grid[row][col] != Shark{-1, -1, -1}) {
        MoveShark(row, col, next_grid);
      }
    }
  }

  grid = next_grid;
}

void Solve() {
  int total_catch_size = 0;
  for (int col = 1; col <= c; ++col) {
    total_catch_size += CatchShark(col);
    MoveSharks();
  }

  cout << total_catch_size << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
