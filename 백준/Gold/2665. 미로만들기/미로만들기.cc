#include <iostream>
#include <deque>
#include <vector>
#include <utility>
using namespace std;

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

int ZeroOneBreadthFirstSearch() {
  deque<pair<int, int>> deq;
  vector<vector<int>> visited(n, vector<int>(n, -1));
  deq.push_back({ 0, 0 });
  visited[0][0] = 0;

  while (!deq.empty()) {
    pair<int, int> p = deq.front();
    int row = p.first;
    int col = p.second;
    deq.pop_front();

    vector<int> move_rows = { 1, 0, -1, 0 };
    vector<int> move_cols = { 0, 1, 0, -1 };
    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (next_row < 0 || next_col < 0 || next_row >= n || next_col >= n)
        continue;
      
      int& visit = visited[next_row][next_col];
      if (visit != -1)
        continue;
      
      char next_val = map[next_row][next_col];
      if (next_val == '0') {
        deq.push_back({ next_row, next_col });
        visit = visited[row][col] + 1;
      } else {
        deq.push_front({ next_row, next_col });
        visit = visited[row][col];
      }
    }
  }

  return visited[n - 1][n - 1];
}

void Solve() {
  int count = ZeroOneBreadthFirstSearch();
  cout << (count == -1 ? 0 : count) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}