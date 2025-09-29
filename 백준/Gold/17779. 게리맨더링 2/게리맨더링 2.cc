#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int n;
vector<vector<int>> populations(20, vector<int>(20));
int answer = numeric_limits<int>::max();

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> populations[i][j];
}

void CalculateMinDiff(int row, int col) {
  for (int d1 = 1; row + d1 < n && col - d1 >= 0; ++d1) {
    for (int d2 = 1; row + d2 < n && col + d2 < n && row + d1 + d2 < n; ++d2) {
      vector<vector<int>> map(n, vector<int>(n));

      // Paint the boundaries.
      for (int i = 0; i <= d1; ++i) {
        map[row + i][col - i] = 5;            // 1st boundary
        map[row + d2 + i][col + d2 - i] = 5;  // 4th boundary
      }

      for (int i = 0; i <= d2; ++i) {
        map[row + i][col + i] = 5;            // 2nd boundary
        map[row + d1 + i][col - d1 + i] = 5;  // 3rd boundary
      }

      // Paint the inner region.
      for (int i = 1; i <= d1; ++i)
        for (int j = 1; map[row + i][col - i + j] != 5; ++j)
          map[row + i][col - i + j] = 5;

      for (int i = 1; i < d2; ++i)
        for (int j = 1; map[row + d1 + i][col - d1 + i + j] != 5; ++j)
          map[row + d1 + i][col - d1 + i + j] = 5;

      // Paint other regions.
      for (int i = 0; i < row + d1; ++i)
        for (int j = 0; j <= col; ++j)
          if (map[i][j] == 0)
            map[i][j] = 1;
          else
            break;

      for (int i = row + d1; i < n; ++i)
        for (int j = 0; j < col - d1 + d2; ++j)
          if (map[i][j] == 0)
            map[i][j] = 3;
          else
            break;

      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (map[i][j] == 0) {
            if (i <= row + d2)
              map[i][j] = 2;
            else
              map[i][j] = 4;
          }
        }
      }

      // Count total populations.
      vector<int> totals(6);
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          totals[map[i][j]] += populations[i][j];

      int max_val = *max_element(totals.begin() + 1, totals.end());
      int min_val = *min_element(totals.begin() + 1, totals.end());
      answer = min(answer, max_val - min_val);
    }
  }
}

void Solve() {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      CalculateMinDiff(i, j);

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
