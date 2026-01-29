#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int n, m;
char arr[52][52];
bool visited[52][52];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      cin >> arr[i][j];
}

int BreadthFirstSearch(pair<int, int> start) {
  bool can_fill = true;
  char min_wall_height = '9';
  queue<pair<int, int>> q;
  vector<pair<int, int>> visits;
  q.push(start);
  visited[start.first][start.second] = true;

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int row = p.first;
    int col = p.second;
    char val = arr[row][col];
    visits.push_back({row, col});
    q.pop();

    int move_rows[4] = {1, 0, -1, 0};
    int move_cols[4] = {0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];
      char next_val = arr[next_row][next_col];

      if (val > next_val) {
        can_fill = false;
        continue;
      } else if (val < next_val) {
        min_wall_height = min(min_wall_height, next_val);
        continue;
      }

      if (visited[next_row][next_col])
        continue;

      q.push({next_row, next_col});
      visited[next_row][next_col] = true;
    }
  }

  int add_up = 0;

  if (can_fill) {
    for (const pair<int, int>& v : visits) {
      add_up += min_wall_height - arr[v.first][v.second];
      arr[v.first][v.second] = min_wall_height;
    }
  }

  return add_up;
}

void Solve() {
  int sum = 0;
  int answer = 0;

  do {
    sum = 0;
    memset(visited, false, sizeof(visited));

    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (!visited[i][j]) {
          sum += BreadthFirstSearch({i, j});

          if (sum > 0)
            break;
        }
      }

      if (sum > 0)
        break;
    }

    answer += sum;
  } while (sum > 0);

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
