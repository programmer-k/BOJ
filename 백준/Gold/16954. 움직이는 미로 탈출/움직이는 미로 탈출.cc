#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

const int kMapSize = 8;
vector<vector<char>> map(kMapSize, vector<char>(kMapSize));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  for (int i = 0; i < kMapSize; ++i)
    for (int j = 0; j < kMapSize; ++j)
      cin >> map[i][j];
}

void MoveWalls(queue<pair<int, int>>& q) {
  vector<vector<char>> map_copy(kMapSize, vector<char>(kMapSize, '.'));
  for (int i = 0; i < kMapSize - 1; ++i)
    for (int j = 0; j < kMapSize; ++j)
      if (map[i][j] == '#')
        map_copy[i + 1][j] = map[i][j];

  map = map_copy;
  q.push({-1, -1});
}

void MoveCharacter(queue<pair<int, int>>& q, int row, int col) {
  if (map[row][col] == '#')
    return;

  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      int next_row = row + i;
      int next_col = col + j;

      if (next_row < 0 || next_col < 0 || next_row >= kMapSize ||
          next_col >= kMapSize)
        continue;

      if (map[next_row][next_col] == '#')
        continue;

      q.push({next_row, next_col});
    }
  }
}

bool BreathFirstSearch() {
  queue<pair<int, int>> q;
  q.push({kMapSize - 1, 0});
  q.push({-1, -1});

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int row = p.first;
    int col = p.second;
    q.pop();

    if (row == 0 && col == kMapSize - 1)
      return true;
    else if (row == -1 && col == -1 && q.size() == 0)
      return false;
    else if (row == -1 && col == -1)
      MoveWalls(q);
    else
      MoveCharacter(q, row, col);
  }

  return false;
}

void Solve() {
  cout << BreathFirstSearch() << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
