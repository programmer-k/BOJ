#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

struct Data {
  int row;
  int col;
  int direction;  // 0: vertical, 1: horizontal
};

int n;
vector<vector<char>> map(50, vector<char>(50));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> map[i][j];
}

Data GetPosition(char ch) {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (i > 0 && i < n - 1 && map[i - 1][j] == ch && map[i][j] == ch &&
          map[i + 1][j] == ch)
        return {i, j, 0};
      else if (j > 0 && j < n - 1 && map[i][j - 1] == ch && map[i][j] == ch &&
               map[i][j + 1] == ch)
        return {i, j, 1};
  return {-1, -1, -1};
}

int BreadthFirstSearch(const Data& start, const Data& end) {
  queue<Data> q;
  vector<vector<vector<int>>> visited(
      n, vector<vector<int>>(n, vector<int>(2, -1)));
  q.push(start);
  visited[start.row][start.col][start.direction] = 0;

  while (!q.empty()) {
    Data data = q.front();
    int row = data.row;
    int col = data.col;
    int direction = data.direction;
    q.pop();

    // {Up, Down, Left, Right, Turn}
    vector<vector<pair<int, int>>> vertical_checks = {
        {{-2, 0}},
        {{2, 0}},
        {{-1, -1}, {0, -1}, {1, -1}},
        {{-1, 1}, {0, 1}, {1, 1}},
        {{-1, -1}, {0, -1}, {1, -1}, {-1, 1}, {0, 1}, {1, 1}}};

    vector<vector<pair<int, int>>> horizontal_checks = {
        {{-1, -1}, {-1, 0}, {-1, 1}},
        {{1, -1}, {1, 0}, {1, 1}},
        {{0, -2}},
        {{0, 2}},
        {{-1, -1}, {-1, 0}, {-1, 1}, {1, -1}, {1, 0}, {1, 1}}};

    vector<bool> are_valid;
    const vector<vector<pair<int, int>>>& checks =
        (direction == 0 ? vertical_checks : horizontal_checks);
    for (const vector<pair<int, int>>& check : checks) {
      bool is_valid = true;
      for (const pair<int, int>& p : check) {
        int next_row = row + p.first;
        int next_col = col + p.second;

        if (next_row < 0 || next_col < 0 || next_row >= n || next_col >= n) {
          is_valid = false;
          break;
        }

        if (map[next_row][next_col] == '1') {
          is_valid = false;
          break;
        }
      }
      are_valid.push_back(is_valid);
    }

    vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}};
    for (int i = 0; i < ssize(are_valid); ++i) {
      if (are_valid[i]) {
        int next_row = row + moves[i].first;
        int next_col = col + moves[i].second;
        int next_direction = (i == 4 ? (direction == 1 ? 0 : 1) : direction);

        if (visited[next_row][next_col][next_direction] != -1)
          continue;

        q.push({next_row, next_col, next_direction});
        visited[next_row][next_col][next_direction] =
            visited[row][col][direction] + 1;
      }
    }
  }

  return visited[end.row][end.col][end.direction] == -1
             ? 0
             : visited[end.row][end.col][end.direction];
}

void Solve() {
  Data start = GetPosition('B');
  Data end = GetPosition('E');
  cout << BreadthFirstSearch(start, end) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
