#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<char>> map(4, vector<char>(4));
vector<vector<bool>> visited(4, vector<bool>(4));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> map[i][j];
}

int FindGreatestNum(int index, int total, int depth) {
  if (index == n * m)
    return total;
  
  int row = index / m;
  int col = index % m;
  int max_total = 0;

  if (visited[row][col])
    return FindGreatestNum(index + 1, total, depth + 1);

  int val = 0;
  for (int i = row; i < min(row + 4, n); ++i) {
    val = val * 10 + map[i][col] - '0';
    visited[i][col] = true;
    max_total = max(max_total, FindGreatestNum(index + 1, total + val, depth + 1));
  }

  for (int i = row; i < min(row + 4, n); ++i) {
    visited[i][col] = false;
  }

  int recover_until = -1;
  val = 0;
  for (int j = col; j < min(col + 4, m); ++j) {
    if (visited[row][j]) {
      recover_until = j;
      break;
    }
    
    val = val * 10 + map[row][j] - '0';
    visited[row][j] = true;
    max_total = max(max_total, FindGreatestNum(index + 1, total + val, depth + 1));
  }

  int until = recover_until == -1 ? min(col + 4, m) : recover_until;
  for (int j = col; j < until; ++j) {
    visited[row][j] = false;
  }

  return max_total;
}

void Solve() {
  cout << FindGreatestNum(0, 0, 0) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
