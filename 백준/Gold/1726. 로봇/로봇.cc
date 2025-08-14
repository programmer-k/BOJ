#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Position {
  int row;
  int col;
  int direction;
};

int n, m;
vector<vector<int>> map(100, vector<int>(100));
int start_row, start_col, start_direction;
int end_row, end_col, end_direction;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> map[i][j];

  cin >> start_row >> start_col >> start_direction;
  cin >> end_row >> end_col >> end_direction;
}

int GetNextRowIncrement(int direction) {
  if (direction == 3)
    return 1;
  else if (direction == 4)
    return -1;
  return 0;
}

int GetNextColIncrement(int direction) {
  if (direction == 1)
    return 1;
  else if (direction == 2)
    return -1;
  return 0;
}

bool IsInRange(int row, int col) {
  if (row < 0 || col < 0 || row >= n || col >= m)
    return false;
  return true;
}

int GetNextDirection(int direction, int increment) {
  if (increment == 0)
    return direction;
  
  if (direction == 1)
    return increment == -1 ? 4 : 3;
  else if (direction == 2)
    return increment == -1 ? 3 : 4;
  else if (direction == 3)
    return increment == -1 ? 1 : 2;
  return increment == -1 ? 2 : 1;
}

int BreadthFirstSearch() {
  queue<Position> q;
  vector<vector<vector<int>>> visited(n, vector<vector<int>>(m, vector<int>(5, -1)));
  q.push({ start_row - 1, start_col - 1, start_direction });
  visited[start_row - 1][start_col - 1][start_direction] = 0;

  while (!q.empty()) {
    Position pos = q.front();
    int row = pos.row;
    int col = pos.col;
    int direction = pos.direction;
    q.pop();

    // Move forward
    for (int i = 1; i <= 3; ++i) {
      int next_row = row + GetNextRowIncrement(direction) * i;
      int next_col = col + GetNextColIncrement(direction) * i;
      
      if (!IsInRange(next_row, next_col))
        break;
      
      if (map[next_row][next_col] == 1)
        break;
      
      if (visited[next_row][next_col][direction] != -1)
        continue;
      
      q.push({ next_row, next_col, direction });
      visited[next_row][next_col][direction] = visited[row][col][direction] + 1;
    }

    // Change direction
    for (int i = -1; i <= 1; ++i) {
      int next_direction = GetNextDirection(direction, i);
      
      if (visited[row][col][next_direction] != -1)
        continue;
      
      q.push({ row, col, next_direction });
      visited[row][col][next_direction] = visited[row][col][direction] + 1;
    }
  }

  return visited[end_row - 1][end_col - 1][end_direction];
}

void Solve() {
  cout << BreadthFirstSearch() << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
