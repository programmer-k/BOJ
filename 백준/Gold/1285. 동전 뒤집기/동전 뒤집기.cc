#include <cstring>
#include <iostream>
#include <limits>
using namespace std;

int n;
char board[20][20];
char scratch_board[20][20];
int column_counts[20];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> board[i][j];
}

char Flip(char& coin) {
  if (coin == 'H')
    return coin = 'T';
  else
    return coin = 'H';
}

int CalculateMinTailCount(int state) {
  memcpy(scratch_board, board, sizeof(scratch_board));
  memset(column_counts, 0, sizeof(column_counts));

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (state & (1 << i) && Flip(scratch_board[i][j]) == 'H')
        ++column_counts[j];
      else if (scratch_board[i][j] == 'H')
        ++column_counts[j];

  int min_count = 0;
  for (int i = 0; i < n; ++i)
    if (column_counts[i] >= n - column_counts[i])
      min_count += n - column_counts[i];
    else
      min_count += column_counts[i];

  return min_count;
}

void Solve() {
  int answer = numeric_limits<int>::max();
  for (int state = 0; state < 1 << n; ++state)
    answer = min(answer, CalculateMinTailCount(state));

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
