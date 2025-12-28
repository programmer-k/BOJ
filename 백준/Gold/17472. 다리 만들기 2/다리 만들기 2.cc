#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

class UnionFind {
 public:
  UnionFind(int size) : parents_(size) {
    for (int i = 0; i < size; ++i)
      parents_[i] = i;
  }

  int Find(int x) {
    if (parents_[x] == x)
      return x;
    return parents_[x] = Find(parents_[x]);
  }

  bool Union(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y)
      return false;

    parents_[y] = x;
    return true;
  }

 private:
  vector<int> parents_;
};

struct Edge {
  int node1;
  int node2;
  int weight;

  bool operator<(const Edge& rhs) const {
    return tie(weight, node1, node2) < tie(rhs.weight, rhs.node1, rhs.node2);
  }
};

const int kIntMax = numeric_limits<int>::max();

int n, m;
vector<vector<int>> input_map(10, vector<int>(10));
vector<vector<int>> area_map(10, vector<int>(10));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> input_map[i][j];
}

void BreadthFirstSearch(pair<int, int> start, int val) {
  queue<pair<int, int>> q;
  q.push(start);
  area_map[start.first][start.second] = val;

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

      if (next_row < 0 || next_row >= n || next_col < 0 || next_col >= m)
        continue;

      if (input_map[next_row][next_col] == 0)
        continue;

      if (area_map[next_row][next_col] != 0)
        continue;

      q.push({next_row, next_col});
      area_map[next_row][next_col] = val;
    }
  }
}

int GetOppositeDirection(int direction) {
  if (direction == 0)
    return 2;
  else if (direction == 1)
    return 3;
  else if (direction == 2)
    return 0;
  else
    return 1;
}

void CalculateAllEdges(vector<vector<int>>& edges) {
  vector<int> move_rows = {1, 0, -1, 0};
  vector<int> move_cols = {0, 1, 0, -1};

  for (int row = 0; row < n; ++row) {
    for (int col = 0; col < m; ++col) {
      for (int direction = 0; direction < 4; ++direction) {
        int from_row = row + move_rows[direction];
        int from_col = col + move_cols[direction];

        if (from_row < 0 || from_row >= n || from_col < 0 || from_col >= m)
          continue;

        if (area_map[row][col] == 0 && area_map[from_row][from_col] != 0) {
          int to_row = row;
          int to_col = col;
          int opposite_direction = GetOppositeDirection(direction);

          while ((to_row >= 0 && to_row < n && to_col >= 0 && to_col < m) &&
                 area_map[to_row][to_col] == 0) {
            to_row += move_rows[opposite_direction];
            to_col += move_cols[opposite_direction];
          }

          if (to_row < 0 || to_row >= n || to_col < 0 || to_col >= m)
            continue;

          int from = area_map[from_row][from_col];
          int to = area_map[to_row][to_col];
          int dist = max(abs(to_row - from_row), abs(to_col - from_col)) - 1;

          if (dist <= 1)
            continue;

          edges[from][to] = min(edges[from][to], dist);
          edges[to][from] = min(edges[to][from], dist);
        }
      }
    }
  }
}

int Kruskal(const vector<vector<int>>& matrix_edge, int area) {
  vector<Edge> edges;

  for (int i = 1; i < ssize(matrix_edge); ++i)
    for (int j = i; j < ssize(matrix_edge[i]); ++j)
      if (matrix_edge[i][j] != kIntMax)
        edges.push_back({i, j, matrix_edge[i][j]});

  sort(edges.begin(), edges.end());

  int count = 0;
  int total = 0;
  UnionFind union_find(area + 1);
  for (const Edge& edge : edges) {
    if (union_find.Union(edge.node1, edge.node2)) {
      total += edge.weight;
      ++count;
    }
  }

  if (count != area - 1)
    return -1;

  return total;
}

void Solve() {
  // Distinguish each area in the input map.
  int area_count = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (input_map[i][j] == 1 && area_map[i][j] == 0)
        BreadthFirstSearch({i, j}, ++area_count);

  vector<vector<int>> edges(area_count + 1,
                            vector<int>(area_count + 1, kIntMax));
  CalculateAllEdges(edges);

  cout << Kruskal(edges, area_count) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
