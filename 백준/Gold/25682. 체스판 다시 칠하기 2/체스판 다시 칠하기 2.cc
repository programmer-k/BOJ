#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <algorithm>
using namespace std;

int n, m, k;
vector<vector<char>> board;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> k;

  board.resize(n);
  for (int i = 0; i < n; ++i)
    board[i].resize(m);
  
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> board[i][j];
}

pair<int, int> CalculateMinPaintCount(int i, int j) {
  int count1 = 0;
  int count2 = 0;
  if ((i + j) % 2 == 0) {
    if (board[i][j] == 'W') {
      ++count2;
    } else {
      ++count1;
    }
  } else {
    if (board[i][j] == 'W') {
      ++count1;
    } else {
      ++count2;
    }
  }

  return make_pair(count1, count2);
}

void Solve() {
  vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(m));
  
  for (int i = 0; i < n; ++i) {
    pair<int, int> sum(0, 0);
    for (int j = 0; j < m; ++j) {
      pair<int, int> p = CalculateMinPaintCount(i, j);
      
      sum.first += p.first;
      sum.second += p.second;

      dp[i][j].first = sum.first + (i > 0 ? dp[i - 1][j].first : 0);
      dp[i][j].second = sum.second + (i > 0 ? dp[i - 1][j].second : 0);
    }
  }

  int min_val = numeric_limits<int>::max();
  for (int i = k - 1; i < n; ++i) {
    for (int j = k - 1; j < m; ++j) {
      int candidate1 = dp[i][j].first - (i >= k ? dp[i - k][j].first : 0) - (j >= k ? dp[i][j - k].first : 0) + (i >= k && j >= k ? dp[i - k][j - k].first : 0);
      int candidate2 = dp[i][j].second - (i >= k ? dp[i - k][j].second : 0) - (j >= k ? dp[i][j - k].second : 0) + (i >= k && j >= k ? dp[i - k][j - k].second : 0);
      min_val = min({ min_val, candidate1, candidate2 });
    }
  }

  cout << min_val << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}