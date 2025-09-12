#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n, m, k;
vector<vector<char>> map(100, vector<char>(100));
string word;
vector<vector<vector<int>>> dp(100,
                               vector<vector<int>>(100, vector<int>(80, -1)));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> k;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> map[i][j];
  cin >> word;
}

int DepthFirstSearch(int row, int col, int index) {
  if (index >= ssize(word))
    return 1;

  if (dp[row][col][index] != -1)
    return dp[row][col][index];

  int total = 0;
  for (int i = -k; i <= k; ++i) {
    if (i == 0)
      continue;

    int next_row = row + i;
    if (next_row < 0 || next_row >= n)
      continue;

    if (map[next_row][col] != word[index])
      continue;

    total += DepthFirstSearch(next_row, col, index + 1);
  }

  for (int i = -k; i <= k; ++i) {
    if (i == 0)
      continue;

    int next_col = col + i;
    if (next_col < 0 || next_col >= m)
      continue;

    if (map[row][next_col] != word[index])
      continue;

    total += DepthFirstSearch(row, next_col, index + 1);
  }

  return dp[row][col][index] = total;
}

void Solve() {
  int answer = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (map[i][j] == word[0])
        answer += DepthFirstSearch(i, j, 1);

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
