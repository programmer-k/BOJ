#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int n, m;
vector<vector<char>> house(50, vector<char>(50));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      cin >> house[i][j];
}

void Init(vector<pair<int, int>>& picks) {
  pair<int, int> start, end;

  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      if (house[i][j] == 'S')
        start = make_pair(i, j);
      else if (house[i][j] == 'E')
        end = make_pair(i, j);
      else if (house[i][j] == 'X')
        picks.push_back({i, j});

  picks.insert(picks.begin(), start);
  picks.push_back(end);
}

void BreadthFirstSearch(pair<int, int> start, vector<int>& dist,
                        const vector<pair<int, int>>& picks) {
  queue<pair<int, int>> q;
  vector<vector<int>> visited(m, vector<int>(n, -1));
  q.push(start);
  visited[start.first][start.second] = 0;

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int row = p.first;
    int col = p.second;
    q.pop();

    vector<int> move_rows = {1, 0, -1, 0};
    vector<int> move_cols = {0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (next_row < 0 || next_col < 0 || next_row >= m || next_col >= n)
        continue;

      if (house[next_row][next_col] == '#')
        continue;

      if (visited[next_row][next_col] != -1)
        continue;

      q.push({next_row, next_col});
      visited[next_row][next_col] = visited[row][col] + 1;
    }
  }

  for (int i = 0; i < ssize(dist); ++i)
    dist[i] = visited[picks[i].first][picks[i].second];
}

int CalculateMinDistance(int count, int dist, vector<int>& selects,
                         vector<bool>& visited,
                         const vector<vector<int>>& dists) {
  if (count == ssize(visited) - 1) {
    return dist + dists[selects.back()][ssize(dists) - 1];
  }

  int min_val = numeric_limits<int>::max();
  for (int i = 1; i < ssize(dists) - 1; ++i) {
    if (!visited[i]) {
      int next_dist = dist + dists[selects.back()][i];
      visited[i] = true;
      selects.push_back(i);
      min_val = min(min_val, CalculateMinDistance(count + 1, next_dist, selects,
                                                  visited, dists));
      visited[i] = false;
      selects.pop_back();
    }
  }

  return min_val;
}

void Solve() {
  vector<pair<int, int>> picks;
  Init(picks);

  vector<vector<int>> dists(ssize(picks), vector<int>(ssize(picks)));
  for (int i = 0; i < ssize(picks); ++i)
    BreadthFirstSearch(picks[i], dists[i], picks);

  vector<bool> visited(ssize(dists));
  vector<int> selects;
  visited[0] = true;
  selects.push_back(0);

  cout << CalculateMinDistance(1, 0, selects, visited, dists) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
