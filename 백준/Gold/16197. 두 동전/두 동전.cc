#include <iostream>
#include <vector>
#include <utility>
#include <limits>
using namespace std;

int n, m;
vector<vector<char>> board(20, vector<char>(20));
vector<int> move_rows = { 1, 0, -1, 0 };
vector<int> move_cols = { 0, 1, 0, -1 };

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> board[i][j];
}

void FindCoins(vector<pair<int, int>>& coins) {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (board[i][j] == 'o')
        coins.push_back({ i, j });
}

bool IsOutOfBound(pair<int, int> p) {
  if (p.first < 0 || p.first >= n || p.second < 0 || p.second >= m)
    return true;
  return false;
}

int DepthFirstSearch(pair<int, int> coin1, pair<int, int> coin2, int depth) {
  if (depth > 10)
    return numeric_limits<int>::max();

  int min_depth = numeric_limits<int>::max();
  for (int i = 0; i < 4; ++i) {
    pair<int, int> next1(coin1.first + move_rows[i], coin1.second + move_cols[i]);
    pair<int, int> next2(coin2.first + move_rows[i], coin2.second + move_cols[i]);

    bool is_next1_dropped = IsOutOfBound(next1);
    bool is_next2_dropped = IsOutOfBound(next2);

    if (is_next1_dropped && is_next2_dropped)
      continue;
    
    if (is_next1_dropped || is_next2_dropped) {
      if (depth + 1 <= 10)
        min_depth = min(min_depth, depth + 1);
      continue;
    }

    char next_val1 = board[next1.first][next1.second];
    char next_val2 = board[next2.first][next2.second];
    
    if (next_val1 == '#')
      next1 = coin1;
    if (next_val2 == '#')
      next2 = coin2;
    
    min_depth = min(min_depth, DepthFirstSearch(next1, next2, depth + 1));
  }

  return min_depth;
}

void Solve() {
  vector<pair<int, int>> coins;
  FindCoins(coins);
  
  int min_count = DepthFirstSearch(coins[0], coins[1], 0);
  if (min_count == numeric_limits<int>::max())
    cout << "-1\n";
  else
    cout << min_count << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}