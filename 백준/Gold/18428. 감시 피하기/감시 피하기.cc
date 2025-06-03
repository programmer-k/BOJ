#include <stdio.h>
#include <stdbool.h>

int n;
char map[6][6];

void GetInput() {
  scanf("%d", &n);
  char temp;
  scanf("%c", &temp);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      scanf("%c%c", &map[i][j], &temp);
}

bool CanHide() {
  bool can_hide = true;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (map[i][j] != 'T')
        continue;
      
      // Right
      for (int k = j + 1; k < n; ++k) {
        if (map[i][k] == 'S')
          return false;
        else if (map[i][k] == 'O')
          break;
      }

      // Bottom
      for (int k = i + 1; k < n; ++k) {
        if (map[k][j] == 'S')
          return false;
        else if (map[k][j] == 'O')
          break;
      }

      // Left
      for (int k = j - 1; k >= 0; --k) {
        if (map[i][k] == 'S')
          return false;
        else if (map[i][k] == 'O')
          break;
      }

      // Up
      for (int k = i - 1; k >= 0; --k) {
        if (map[k][j] == 'S')
          return false;
        else if (map[k][j] == 'O')
          break;
      }
    }
  }

  return true;
}

void Solve() {
  bool can_hide = false;
  int n_square = n * n;
  for (int i = 0; i < n_square; ++i) {
    for (int j = i + 1; j < n_square; ++j) {
      for (int k = j + 1; k < n_square; ++k) {
        int i_row = i / n;
        int i_col = i % n;
        int j_row = j / n;
        int j_col = j % n;
        int k_row = k / n;
        int k_col = k % n;

        if (map[i_row][i_col] == 'X' && map[j_row][j_col] == 'X' && map[k_row][k_col] == 'X') {
          map[i_row][i_col] = 'O';
          map[j_row][j_col] = 'O';
          map[k_row][k_col] = 'O';
          
          if (CanHide())
            can_hide = true;

          map[i_row][i_col] = 'X';
          map[j_row][j_col] = 'X';
          map[k_row][k_col] = 'X';
        }
      }
    }
  }

  if (can_hide)
    printf("YES\n");
  else
    printf("NO\n");
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}