#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int n, m, g, r;
int garden[50][50];
vector<pair<int, int>> candidates;
vector<int> greens, reds;
int visited[2][50][50];
int move_rows[4] = {1, 0, -1, 0};
int move_cols[4] = {0, 1, 0, -1};
int max_flower_count = 0;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> g >> r;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> garden[i][j];
}

void FindAllCandidates() {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (garden[i][j] == 2)
        candidates.push_back({i, j});
}

void BreadthFirstSearch() {
  int flower_count = 0;
  queue<pair<int, int>> q;
  memset(visited, -1, sizeof(visited));

  for (int green : greens) {
    q.push(candidates[green]);
    visited[0][candidates[green].first][candidates[green].second] = 0;
  }

  for (int red : reds) {
    q.push(candidates[red]);
    visited[1][candidates[red].first][candidates[red].second] = 0;
  }

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int row = p.first;
    int col = p.second;
    q.pop();

    if (visited[0][row][col] != -1 && visited[1][row][col] != -1)
      continue;

    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (next_row < 0 || next_col < 0 || next_row >= n || next_col >= m)
        continue;

      int next_val = garden[next_row][next_col];
      if (next_val == 0)
        continue;

      if (visited[0][row][col] != -1 && (visited[0][next_row][next_col] != -1 ||
                                         visited[1][next_row][next_col] != -1))
        continue;

      if (visited[1][row][col] != -1 && visited[1][next_row][next_col] != -1)
        continue;

      if (visited[1][row][col] != -1 && visited[0][next_row][next_col] != -1 &&
          visited[1][row][col] + 1 != visited[0][next_row][next_col])
        continue;

      q.push({next_row, next_col});
      if (visited[0][row][col] != -1)
        visited[0][next_row][next_col] = visited[0][row][col] + 1;
      else
        visited[1][next_row][next_col] = visited[1][row][col] + 1;

      if (visited[1][row][col] != -1 && visited[0][next_row][next_col] != -1 &&
          visited[1][row][col] + 1 == visited[0][next_row][next_col])
        ++flower_count;
    }
  }

  max_flower_count = max(max_flower_count, flower_count);
}

void GenerateAll(int index, int green, int red, int none) {
  if (green > g || red > r || none > ssize(candidates) - g - r)
    return;

  if (index == ssize(candidates)) {
    BreadthFirstSearch();
    return;
  }

  greens.push_back(index);
  GenerateAll(index + 1, green + 1, red, none);
  greens.pop_back();

  reds.push_back(index);
  GenerateAll(index + 1, green, red + 1, none);
  reds.pop_back();

  GenerateAll(index + 1, green, red, none + 1);
}

void Solve() {
  FindAllCandidates();
  GenerateAll(0, 0, 0, 0);
  cout << max_flower_count << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
