#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Data {
  int row;
  int col;
  int step;
};

int h, w;
vector<vector<char>> map(1'000, vector<char>(1'000));
vector<vector<int>> state(1'000, vector<int>(1'000));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> h >> w;

  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      cin >> map[i][j];
}

void InitState(int row, int col) {
  int val = 0;
  for (int i = row - 1; i <= row + 1; ++i)
    for (int j = col - 1; j <= col + 1; ++j)
      if (map[i][j] == -1)
        ++val;
  state[row][col] = val;
}

void Push(queue<Data>& q, int row, int col, int step) {
  q.push({row, col, step});
  map[row][col] = -1;
}

void Solve() {
  // Update map input data.
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      if (map[i][j] == '.')
        map[i][j] = -1;
      else
        map[i][j] -= '0';

  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      if (map[i][j] != -1)
        InitState(i, j);

  queue<Data> q;
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      if (map[i][j] != -1 && state[i][j] >= map[i][j])
        Push(q, i, j, 1);

  int answer = 0;
  while (!q.empty()) {
    Data data = q.front();
    int row = data.row;
    int col = data.col;
    int step = data.step;
    q.pop();

    answer = max(answer, step);
    for (int i = row - 1; i <= row + 1; ++i)
      for (int j = col - 1; j <= col + 1; ++j)
        if (map[i][j] != -1 && ++state[i][j] >= map[i][j])
          Push(q, i, j, step + 1);
  }

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
