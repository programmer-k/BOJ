#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

struct Block {
  int t;
  int x;
  int y;
};

int n;
vector<Block> blocks;
vector<vector<bool>> map(10, vector<bool>(10));
int score;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  blocks.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> blocks[i].t >> blocks[i].x >> blocks[i].y;
}

bool IsValid(const vector<pair<int, int>> positions) {
  for (const pair<int, int>& position : positions) {
    if (position.first >= 10 || position.second >= 10)
      return false;

    if (map[position.first][position.second])
      return false;
  }

  return true;
}

void MoveBlock(vector<pair<int, int>> positions, bool move_bottom) {
  // Move until it reaches invalid position.
  while (IsValid(positions)) {
    for (pair<int, int>& position : positions)
      if (move_bottom)
        ++position.first;
      else
        ++position.second;
  }

  // Rollback from the last invalid position.
  for (pair<int, int>& position : positions)
    if (move_bottom)
      --position.first;
    else
      --position.second;

  // Mark the current position as occupied.
  for (const pair<int, int>& position : positions)
    map[position.first][position.second] = true;
}

void DeleteRow(int row) {
  for (int i = row; i >= 4; --i)
    for (int j = 0; j < 4; ++j)
      map[i][j] = map[i - 1][j];
}

void DeleteFullRows() {
  for (int i = 9; i >= 6; --i) {
    bool is_full = true;
    for (int j = 0; j < 4; ++j)
      if (!map[i][j])
        is_full = false;

    if (!is_full)
      continue;

    DeleteRow(i);
    ++score;
    ++i;
  }
}

void DeleteCol(int col) {
  for (int j = col; j >= 4; --j)
    for (int i = 0; i < 4; ++i)
      map[i][j] = map[i][j - 1];
}

void DeleteFullCols() {
  for (int j = 9; j >= 6; --j) {
    bool is_full = true;
    for (int i = 0; i < 4; ++i)
      if (!map[i][j])
        is_full = false;

    if (!is_full)
      continue;

    DeleteCol(j);
    ++score;
    ++j;
  }
}

void DeleteTopRows() {
  set<int> s;
  for (int i = 4; i <= 5; ++i)
    for (int j = 0; j < 4; ++j)
      if (map[i][j])
        s.insert(i);

  for (int i = 0; i < ssize(s); ++i)
    DeleteRow(9);
}

void DeleteTopCols() {
  set<int> s;
  for (int i = 0; i < 4; ++i)
    for (int j = 4; j <= 5; ++j)
      if (map[i][j])
        s.insert(j);

  for (int i = 0; i < ssize(s); ++i)
    DeleteCol(9);
}

void Process(const vector<pair<int, int>>& positions) {
  MoveBlock(positions, true);
  MoveBlock(positions, false);

  DeleteFullRows();
  DeleteFullCols();

  DeleteTopRows();
  DeleteTopCols();
}

void Solve() {
  for (const Block& block : blocks) {
    vector<pair<int, int>> positions = {{block.x, block.y}};

    if (block.t == 2)
      positions.push_back({block.x, block.y + 1});
    else if (block.t == 3)
      positions.push_back({block.x + 1, block.y});

    Process(positions);
  }

  int blue_count = 0, green_count = 0;
  for (int i = 0; i < 4; ++i)
    for (int j = 6; j <= 9; ++j)
      if (map[i][j])
        ++blue_count;

  for (int i = 6; i <= 9; ++i)
    for (int j = 0; j < 4; ++j)
      if (map[i][j])
        ++green_count;

  cout << score << '\n';
  cout << blue_count + green_count << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
