#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
using namespace std;

struct Pos {
  int height;
  int row;
  int col;
};

const int kSize = 5;
const int kIntMax = numeric_limits<int>::max();
vector<vector<vector<int>>> map(kSize,
                                vector<vector<int>>(kSize, vector<int>(kSize)));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  for (int i = 0; i < kSize; ++i)
    for (int j = 0; j < kSize; ++j)
      for (int k = 0; k < kSize; ++k)
        cin >> map[i][j][k];
}

int BreadthFirstSearch(vector<vector<vector<int>>> maze) {
  queue<Pos> q;
  vector<vector<vector<int>>> visited(
      kSize, vector<vector<int>>(kSize, vector<int>(kSize, -1)));

  if (maze[0][0][0] == 1) {
    q.push({0, 0, 0});
    visited[0][0][0] = 0;
  }

  while (!q.empty()) {
    Pos pos = q.front();
    int height = pos.height;
    int row = pos.row;
    int col = pos.col;
    q.pop();

    // Top, bottom, up, down, left, right
    vector<Pos> moves = {{-1, 0, 0}, {1, 0, 0},  {0, -1, 0},
                         {0, 1, 0},  {0, 0, -1}, {0, 0, 1}};
    for (const Pos& move : moves) {
      int next_height = height + move.height;
      int next_row = row + move.row;
      int next_col = col + move.col;

      if (next_height < 0 || next_row < 0 || next_col < 0 ||
          next_height >= kSize || next_row >= kSize || next_col >= kSize)
        continue;

      if (maze[next_height][next_row][next_col] == 0)
        continue;

      if (visited[next_height][next_row][next_col] != -1)
        continue;

      q.push({next_height, next_row, next_col});
      visited[next_height][next_row][next_col] = visited[height][row][col] + 1;
    }
  }

  return visited[kSize - 1][kSize - 1][kSize - 1] != -1
             ? visited[kSize - 1][kSize - 1][kSize - 1]
             : kIntMax;
}

void Rotate(const vector<vector<int>>& maze,
            vector<vector<int>>& rotated_maze) {
  for (int i = 0; i < kSize; ++i)
    for (int j = 0; j < kSize; ++j)
      rotated_maze[j][kSize - 1 - i] = maze[i][j];
}

void Solve() {
  vector<vector<vector<vector<int>>>> full_map(
      4, vector<vector<vector<int>>>(
             kSize, vector<vector<int>>(kSize, vector<int>(kSize))));
  full_map[0] = map;

  for (int i = 1; i < 4; ++i)
    for (int j = 0; j < kSize; ++j)
      Rotate(full_map[i - 1][j], full_map[i][j]);

  int answer = kIntMax;
  vector<int> orders = {0, 1, 2, 3, 4};
  do {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        for (int k = 0; k < 4; ++k)
          for (int m = 0; m < 4; ++m)
            for (int n = 0; n < 4; ++n)
              answer = min(answer,
                           BreadthFirstSearch(
                               {full_map[i][orders[0]], full_map[j][orders[1]],
                                full_map[k][orders[2]], full_map[m][orders[3]],
                                full_map[n][orders[4]]}));
  } while (next_permutation(orders.begin(), orders.end()));

  cout << (answer != kIntMax ? answer : -1) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
