#include <iostream>
#include <array>
#include <iomanip>
using namespace std;

int n;
array<int, 4> probabilities;
array<int, 4> move_rows = { 0, 0, 1, -1 };
array<int, 4> move_cols = { 1, -1, 0, 0 };
array<array<bool, 29>, 29> visited;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < 4; ++i)
    cin >> probabilities[i];
}

double VisitAllPossibleRoutes(int row, int col, int depth) {
  if (depth >= n) {
    return 1.0;
  }

  double prob = 0.0;
  visited[row][col] = true;

  for (int i = 0; i < 4; ++i) {
    int next_row = row + move_rows[i];
    int next_col = col + move_cols[i];

    if (visited[next_row][next_col])
      continue;

    prob += VisitAllPossibleRoutes(next_row, next_col, depth + 1) * probabilities[i] / 100.0;
  }

  visited[row][col] = false;
  return prob;
}

void Solve() {
  cout << setprecision(18) << VisitAllPossibleRoutes(14, 14, 0) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
