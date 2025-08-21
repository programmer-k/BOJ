#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int w, h;
vector<vector<char>> map(100, vector<char>(100));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> w >> h;
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      cin >> map[i][j];
}

int BreadthFirstSearch(pair<int, int> start, pair<int, int> end) {
  queue<pair<int, int>> q;
  vector<vector<int>> visited(h, vector<int>(w, -1));
  q.push(start);

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int row = p.first;
    int col = p.second;
    q.pop();

    vector<int> move_rows = {1, 0, -1, 0};
    vector<int> move_cols = {0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
      int next_row = row;
      int next_col = col;
      while (true) {
        next_row += move_rows[i];
        next_col += move_cols[i];

        if (next_row < 0 || next_col < 0 || next_row >= h || next_col >= w)
          break;

        if (map[next_row][next_col] == '*')
          break;

        if (visited[next_row][next_col] != -1)
          continue;

        q.push({next_row, next_col});
        visited[next_row][next_col] = visited[row][col] + 1;
      }
    }
  }

  return visited[end.first][end.second];
}

void Solve() {
  vector<pair<int, int>> c;
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      if (map[i][j] == 'C')
        c.push_back({i, j});

  cout << BreadthFirstSearch(c[0], c[1]) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}