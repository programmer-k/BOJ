#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

struct Data {
  int dist;
  int row;
  int col;

  bool operator<(const Data& rhs) const {
    return tie(dist, row, col) < tie(rhs.dist, rhs.row, rhs.col);
  }

  bool operator>(const Data& rhs) const {
    return rhs < *this;
  }
};

const int kIntMax = numeric_limits<int>::max();

int n, m, t, d;
vector<vector<char>> char_map(25, vector<char>(25));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> t >> d;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> char_map[i][j];
}

vector<vector<int>> GenerateIntMap() {
  vector<vector<int>> map(n, vector<int>(m));

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (char_map[i][j] <= 'Z')
        map[i][j] = char_map[i][j] - 'A';
      else
        map[i][j] = char_map[i][j] - 'a' + 26;

  return map;
}

vector<vector<int>> Dijkstra(vector<vector<int>>& map, int start_row,
                             int start_col) {
  priority_queue<Data, vector<Data>, greater<Data>> pq;
  vector<vector<int>> dists(n, vector<int>(m, kIntMax));
  pq.push({0, start_row, start_col});
  dists[start_row][start_col] = 0;

  while (!pq.empty()) {
    Data data = pq.top();
    int dist = data.dist;
    int row = data.row;
    int col = data.col;
    int curr_height = map[row][col];
    pq.pop();

    if (dist > dists[row][col])
      continue;

    vector<int> move_rows = {1, 0, -1, 0};
    vector<int> move_cols = {0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (next_row < 0 || next_col < 0 || next_row >= n || next_col >= m)
        continue;

      int next_height = map[next_row][next_col];
      if (abs(next_height - curr_height) > t)
        continue;

      int next_dist =
          dist + (curr_height >= next_height ? 1
                                             : (next_height - curr_height) *
                                                   (next_height - curr_height));
      if (next_dist < dists[next_row][next_col]) {
        pq.push({next_dist, next_row, next_col});
        dists[next_row][next_col] = next_dist;
      }
    }
  }

  return dists;
}

void Solve() {
  vector<vector<int>> map = GenerateIntMap();
  vector<vector<int>> forward_dists = Dijkstra(map, 0, 0);
  vector<vector<int>> backward_dists(n, vector<int>(m));

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      backward_dists[i][j] = Dijkstra(map, i, j)[0][0];

  int max_height = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (forward_dists[i][j] != kIntMax && backward_dists[i][j] != kIntMax &&
          forward_dists[i][j] + backward_dists[i][j] <= d)
        max_height = max(max_height, map[i][j]);

  cout << max_height << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
