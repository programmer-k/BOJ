#include <iostream>
#include <array>
#include <queue>
#include <vector>
#include <utility>
#include <limits>
using namespace std;

int n, m;
array<array<int, 50>, 50> map;
vector<pair<int, int>> viruses;
int min_val = numeric_limits<int>::max();

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> map[i][j];
}

int BreadthFirstSearch(vector<bool>& selected) {
  queue<pair<int, int>> q;
  vector<vector<int>> visited(n, vector<int>(n, -1));

  for (int i = 0; i < ssize(selected); ++i)
    if (selected[i]) {
      q.push(viruses[i]);
      visited[viruses[i].first][viruses[i].second] = 0;
    }

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int row = p.first;
    int col = p.second;
    q.pop();

    vector<int> move_rows = { 1, 0, -1, 0 };
    vector<int> move_cols = { 0, 1, 0, -1 };
    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (next_row < 0 || next_col < 0 || next_row >= n || next_col >= n)
        continue;
      
      int val = map[next_row][next_col];
      if (val == 1)
        continue;
      
      int& visit = visited[next_row][next_col];
      if (visit != -1)
        continue;

      q.push({ next_row, next_col });
      visit = visited[row][col] + 1;
    }
  }

  int max_val = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (map[i][j] != 1) {
        if (visited[i][j] == -1)
          return -1;
        else
          max_val = max(max_val, visited[i][j]);
      }

  return max_val;
}

void FindPossibleVirusLocations() {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (map[i][j] == 2)
        viruses.push_back({ i, j });
}

void SelectVirusLocations(vector<bool>& selected, int index, int count) {
  if (count == m) {
    int val = BreadthFirstSearch(selected);
    if (val != -1)
      min_val = min(min_val, val);
    return;
  }
  
  if (index == ssize(selected)) {
    return;
  }

  for (int i = index; i < ssize(selected); ++i) {
    selected[i] = true;
    SelectVirusLocations(selected, i + 1, count + 1);
    selected[i] = false;
  }
}

void Solve() {
  FindPossibleVirusLocations();

  vector<bool> selected(ssize(viruses), false);
  SelectVirusLocations(selected, 0, 0);

  if (min_val == numeric_limits<int>::max())
    cout << "-1\n";
  else
    cout << min_val << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}