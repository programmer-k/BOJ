#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int n, m, k;
vector<vector<int>> map(10, vector<int>(10, 0));
vector<vector<bool>> selected(10, vector<bool>(10, false));
int max_val = numeric_limits<int>::min();


void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> k;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> map[i][j];
}

void CalcMax(int index, int sum, int rem) {
  if (rem == 0) {
    max_val = max(max_val, sum);
    return;
  }

  if (index == n * m)
    return;

  int row = index / m;
  int col = index % m;
  int val = map[row][col];
  CalcMax(index + 1, sum, rem);

  if ((row == 0 || !selected[row - 1][col]) && (col == 0 || !selected[row][col - 1])) {
    selected[row][col] = true;
    CalcMax(index + 1, sum + val, rem - 1);
    selected[row][col] = false;
  }
}

void Solve() {
  CalcMax(0, 0, k);
  cout << max_val << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}