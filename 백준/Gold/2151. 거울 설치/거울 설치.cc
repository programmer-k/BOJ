#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int n;
vector<vector<char>> map(50, vector<char>(50));
vector<vector<bool>> visited(50, vector<bool>(50));
vector<pair<int, int>> doors;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> map[i][j];
}

int BreadthFirstSearch() {
  queue<pair<int, int>> q;
  vector<vector<int>> visited(n, vector<int>(n, -1));
  q.push(doors[0]);
  visited[doors[0].first][doors[0].second] = 0;

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

        if (next_row < 0 || next_col < 0 || next_row >= n || next_col >= n)
          break;

        if (map[next_row][next_col] == '*')
          break;

        if (visited[next_row][next_col] != -1)
          continue;

        if (map[next_row][next_col] == '!')
          q.push({next_row, next_col});
        visited[next_row][next_col] = visited[row][col] + 1;
      }
    }
  }

  return visited[doors[1].first][doors[1].second] - 1;
}

void Solve() {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (map[i][j] == '#')
        doors.push_back({i, j});

  cout << BreadthFirstSearch() << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
