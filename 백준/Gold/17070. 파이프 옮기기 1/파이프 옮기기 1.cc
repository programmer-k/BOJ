#include <iostream>
using namespace std;

int n;
int map[16][16];
int visit_count;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> map[i][j];
}

// We can assume that the current status is valid.
void Search(int row, int col, int status) {
  //cout << "Search(" << row << ", " << col << ", " << status << ")" << endl;

  // Check whether the search arrives at the destination.
  if (status == 0 && row == n - 1 && col == n - 2)
    ++visit_count;
  else if (status == 1 && row == n - 2 && col == n - 1)
    ++visit_count;
  else if (status == 2 && row == n - 2 && col == n - 2)
    ++visit_count;

  // Identify the current status and move forward based on it.
  if (status == 0) {
    // Status 0: parallel
    if (col + 2 < n && map[row][col + 2] == 0)
      Search(row, col + 1, 0);
    if (row + 1 < n && col + 2 < n && map[row][col + 2] == 0 && map[row + 1][col + 1] == 0 && map[row + 1][col + 2] == 0)
      Search(row, col + 1, 2);
  } else if (status == 1) {
    // Status 1: vertical
    if (row + 2 < n && map[row + 2][col] == 0)
      Search(row + 1, col, 1);
    if (row + 2 < n && col + 1 < n && map[row + 1][col + 1] == 0 && map[row + 2][col + 1] == 0 && map[row + 2][col] == 0)
      Search(row + 1, col, 2);
  } else {
    // Status 2: diagonal
    if (row + 1 < n && col + 2 < n && map[row + 1][col + 2] == 0)
      Search(row + 1, col + 1, 0);
    if (row + 2 < n && col + 1 < n && map[row + 2][col + 1] == 0)
      Search(row + 1, col + 1, 1);
    if (row + 2 < n && col + 2 < n && map[row + 2][col + 1] == 0 && map[row + 2][col + 2] == 0 && map[row + 1][col + 2] == 0)
      Search(row + 1, col + 1, 2);
  }
}

void Solve() {
  Search(0, 0, 0);
  cout << visit_count << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}