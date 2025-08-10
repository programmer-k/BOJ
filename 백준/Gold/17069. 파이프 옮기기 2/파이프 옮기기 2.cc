#include <iostream>
#include <vector>
#include <utility>
#include <cstdint>
using namespace std;

int n;
vector<vector<int>> map;
vector<vector<vector<int64_t>>> dp;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  map.resize(n);
  for (int i = 0; i < n; ++i)
    map[i].resize(n);

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> map[i][j];
}

bool HasArrived(int row, int col, int state) {
  if (state == 0 && row == n - 1 && col == n - 2)
    return true;
  if (state == 1 && row == n - 2 && col == n - 1)
    return true;
  if (state == 2 && row == n - 2 && col == n - 2)
    return true;
  return false;
}

bool CanMove(int row, int col, const vector<pair<int, int>> moves) {
  for (const pair<int, int>& move : moves) {
    int next_row = row + move.first;
    int next_col = col + move.second;

    if (next_row >= n || next_col >= n)
      return false;

    if (map[next_row][next_col] == 1)
      return false;
  }

  return true;
}

int64_t DepthFirstSearch(int row, int col, int state) {
  if (dp[row][col][state] != -1)
    return dp[row][col][state];
  
  if (HasArrived(row, col, state))
    return dp[row][col][state] = 1;
  
  int64_t total = 0;
  if (state == 0) {
    vector<pair<int, int>> move_right = {{ 0, 2 }};
    vector<pair<int, int>> move_right_down = {{ 0, 2 }, { 1, 2 }, { 1, 1 }};
    int next_row = row;
    int next_col = col + 1;

    if (CanMove(row, col, move_right))
      total += DepthFirstSearch(next_row, next_col, 0);
    
    if (CanMove(row, col, move_right_down))
      total += DepthFirstSearch(next_row, next_col, 2);

  } else if (state == 1) {
    vector<pair<int, int>> move_down = {{ 2, 0 }};
    vector<pair<int, int>> move_right_down = {{ 1, 1 }, { 2, 0 }, { 2, 1 }};
    int next_row = row + 1;
    int next_col = col;

    if (CanMove(row, col, move_down))
      total += DepthFirstSearch(next_row, next_col, 1);
    
    if (CanMove(row, col, move_right_down))
      total += DepthFirstSearch(next_row, next_col, 2);

  } else {
    vector<pair<int, int>> move_right = {{ 1, 2 }};
    vector<pair<int, int>> move_down = {{ 2, 1 }};
    vector<pair<int, int>> move_right_down = {{ 1, 2 }, { 2, 1 }, { 2, 2 }};
    int next_row = row + 1;
    int next_col = col + 1;

    if (CanMove(row, col, move_right))
      total += DepthFirstSearch(next_row, next_col, 0);

    if (CanMove(row, col, move_down))
      total += DepthFirstSearch(next_row, next_col, 1);
    
    if (CanMove(row, col, move_right_down))
      total += DepthFirstSearch(next_row, next_col, 2);
  }

  return dp[row][col][state] = total;
}

void Solve() {
  dp.resize(n);
  for (int i = 0; i < n; ++i) {
    dp[i].resize(n);
    for (int j = 0; j < n; ++j) {
      dp[i][j].resize(3, -1);
    }
  }

  cout << DepthFirstSearch(0, 0, 0) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
