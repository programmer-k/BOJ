#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

const int kIntMax = numeric_limits<int>::max();

int n, m;
vector<vector<char>> forests(52, vector<char>(52));
vector<vector<bool>> is_next_to_waste(52, vector<bool>(52));

struct Data {
  int row;
  int col;
  int garbage_count;
  int nearby_garbage_count;

  bool operator<(const Data& rhs) const {
    return tie(garbage_count, nearby_garbage_count, row, col) <
           tie(rhs.garbage_count, rhs.nearby_garbage_count, rhs.row, rhs.col);
  }

  bool operator>(const Data& rhs) const {
    return rhs < *this;
  }
};

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      cin >> forests[i][j];
}

pair<int, int> FindPos(char ch) {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (forests[i][j] == ch)
        return {i, j};
  return {-1, -1};
}

void InitIsNextToWaste() {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (forests[i][j] == '.')
        if (forests[i + 1][j] == 'g' || forests[i - 1][j] == 'g' ||
            forests[i][j + 1] == 'g' || forests[i][j - 1] == 'g')
          is_next_to_waste[i][j] = true;
}

pair<int, int> Dijkstra(pair<int, int> start, pair<int, int> end) {
  priority_queue<Data, vector<Data>, greater<Data>> pq;
  vector<vector<pair<int, int>>> dists(
      n + 1, vector<pair<int, int>>(m + 1, {kIntMax, kIntMax}));
  pq.push({start.first, start.second, 0, 0});
  dists[start.first][start.second] = {0, 0};

  while (!pq.empty()) {
    Data data = pq.top();
    int row = data.row;
    int col = data.col;
    int garbage_count = data.garbage_count;
    int nearby_garbage_count = data.nearby_garbage_count;
    pq.pop();

    if (row == end.first && col == end.second)
      return {garbage_count, nearby_garbage_count};

    vector<int> move_rows = {1, 0, -1, 0};
    vector<int> move_cols = {0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (next_row <= 0 || next_col <= 0 || next_row > n || next_col > m)
        continue;

      int next_garbage_count =
          garbage_count + (forests[next_row][next_col] == 'g');
      int next_nearby_garbage_count =
          nearby_garbage_count + is_next_to_waste[next_row][next_col];
      pair<int, int> next_dist(next_garbage_count, next_nearby_garbage_count);

      if (next_dist < dists[next_row][next_col]) {
        pq.push({next_row, next_col, next_garbage_count,
                 next_nearby_garbage_count});
        dists[next_row][next_col] = next_dist;
      }
    }
  }

  return {-1, -1};
}

void Solve() {
  InitIsNextToWaste();
  pair<int, int> start_pos = FindPos('S');
  pair<int, int> flower_pos = FindPos('F');
  pair<int, int> answer = Dijkstra(start_pos, flower_pos);
  cout << answer.first << ' ' << answer.second << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
