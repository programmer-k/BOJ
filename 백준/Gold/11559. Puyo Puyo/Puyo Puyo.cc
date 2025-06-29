#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <array>
using namespace std;

const int kRow = 12;
const int kCol = 6;
vector<vector<char>> map(kRow, vector<char>(kCol));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  for (int i = 0; i < kRow; ++i)
    for (int j = 0; j < kCol; ++j)
      cin >> map[i][j];
}

int BreadthFirstSearchCount(int start_row, int start_col, vector<pair<int, int>>* coordinates = nullptr) {
  int count = 0;
  const char kColor = map[start_row][start_col];
  queue<pair<int, int>> q;
  vector<vector<bool>> visited(kRow, vector<bool>(kCol));
  
  q.push({ start_row, start_col });
  visited[start_row][start_col] = true;

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int row = p.first;
    int col = p.second;
    q.pop();
    ++count;

    if (coordinates != nullptr)
      coordinates->push_back({ row, col });

    const int kArrSize = 4;
    array<int, kArrSize> move_rows = { 1, 0, -1, 0 };
    array<int, kArrSize> move_cols = { 0, 1, 0, -1 };
    for (int i = 0; i < kArrSize; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (next_row < 0 || next_col < 0 || next_row >= kRow || next_col >= kCol)
        continue;
      
      if (map[next_row][next_col] != kColor)
        continue;
      
      if (visited[next_row][next_col])
        continue;

      q.push({ next_row, next_col });
      visited[next_row][next_col] = true;
    }
  }

  return count;
}

bool IsGameOver() {
  for (int i = 0; i < kRow; ++i)
    for (int j = 0; j < kCol; ++j)
      if (map[i][j] != '.' && BreadthFirstSearchCount(i, j) >= 4)
        return false;
  return true;
}

void PlayGame() {
  for (int i = 0; i < kRow; ++i) {
    for (int j = 0; j < kCol; ++j) {
      vector<pair<int, int>> coordinates;
      if (map[i][j] != '.' && BreadthFirstSearchCount(i, j, &coordinates) >= 4) {
        for (pair<int, int> p : coordinates) {
          map[p.first][p.second] = '.';
        }
      }
    }
  }

  vector<vector<char>> new_map(kRow, vector<char>(kCol, '.'));
  for (int j = 0; j < kCol; ++j) {
    int count = 0;
    for (int i = kRow - 1; i >= 0; --i) {
      if (map[i][j] == '.')
        ++count;
      else
        new_map[i + count][j] = map[i][j];
    }
  }
  map = new_map;
}

void Solve() {
  int count = 0;
  
  while (!IsGameOver()) {
    PlayGame();
    ++count;
  }

  cout << count << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}