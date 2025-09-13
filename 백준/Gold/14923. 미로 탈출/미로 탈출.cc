#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Data {
  int row;
  int col;
  int stick;
};

int n, m;
int hx, hy, ex, ey;
vector<vector<int>> map(1'001, vector<int>(1'001));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  cin >> hx >> hy;
  cin >> ex >> ey;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      cin >> map[i][j];
}

int BreadthFirstSearch() {
  queue<Data> q;
  vector<vector<vector<int>>> visited(2, vector<vector<int>>(n + 1, vector<int>(m + 1, -1)));
  q.push({hx, hy, 0});
  visited[0][hx][hy] = 0;
  
  while (!q.empty()) {
    Data data = q.front();
    int row = data.row;
    int col = data.col;
    int stick = data.stick;
    q.pop();

    vector<int> move_rows = {1, 0, -1, 0};
    vector<int> move_cols = {0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (next_row <= 0 || next_col <= 0 || next_row > n || next_col > m)
        continue;
      
      if (map[next_row][next_col] == 0) {
        if (visited[stick][next_row][next_col] != -1)
          continue;
        
        q.push({next_row, next_col, stick});
        visited[stick][next_row][next_col] = visited[stick][row][col] + 1;
      } else {
        if (stick == 1)
          continue;
        
        if (visited[1][next_row][next_col] != -1)
          continue;
        
        q.push({next_row, next_col, 1});
        visited[1][next_row][next_col] = visited[stick][row][col] + 1;
      }
    }
  }

  if (visited[0][ex][ey] == -1 && visited[1][ex][ey] == -1)
    return -1;
  else if (visited[0][ex][ey] == -1)
    return visited[1][ex][ey];
  else if (visited[1][ex][ey] == -1)
    return visited[0][ex][ey];
  return min(visited[0][ex][ey], visited[1][ex][ey]);
}

void Solve() {
  cout << BreadthFirstSearch() << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
