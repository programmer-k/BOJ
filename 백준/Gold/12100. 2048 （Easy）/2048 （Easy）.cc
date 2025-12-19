#include <iostream>
#include <vector>
using namespace std;

enum Direction { kUp, kDown, kLeft, kRight };

int n;
vector<vector<int>> board(20, vector<int>(20));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> board[i][j];
}

int GetMaxValue(const vector<vector<int>>& board) {
  int max_val = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      max_val = max(max_val, board[i][j]);
  return max_val;
}

int DepthFirstSearch(const vector<vector<int>>& current_board, int step) {
  if (step == 5)
    return GetMaxValue(current_board);

  int max_val = 0;
  for (int direction = 0; direction < 4; ++direction) {
    vector<vector<int>> next_board(current_board);

    if (direction == kUp) {
      for (int j = 0; j < n; ++j) {
        vector<bool> unites(1);
        for (int i = 0; i < n; ++i) {
          if (next_board[i][j] > 0) {
            bool unite = false;
            for (int next_i = i; next_i > 0; --next_i) {
              if (next_board[next_i - 1][j] == 0) {
                next_board[next_i - 1][j] = next_board[next_i][j];
                next_board[next_i][j] = 0;
              } else if (next_board[next_i][j] == next_board[next_i - 1][j] &&
                         !unites.back()) {
                next_board[next_i - 1][j] *= 2;
                next_board[next_i][j] = 0;
                unite = true;
                break;
              } else {
                break;
              }
            }
            unites.push_back(unite);
          }
        }
      }
    } else if (direction == kDown) {
      for (int j = 0; j < n; ++j) {
        vector<bool> unites(1);
        for (int i = n - 1; i >= 0; --i) {
          if (next_board[i][j] > 0) {
            bool unite = false;
            for (int next_i = i; next_i < n - 1; ++next_i) {
              if (next_board[next_i + 1][j] == 0) {
                next_board[next_i + 1][j] = next_board[next_i][j];
                next_board[next_i][j] = 0;
              } else if (next_board[next_i][j] == next_board[next_i + 1][j] &&
                         !unites.back()) {
                next_board[next_i + 1][j] *= 2;
                next_board[next_i][j] = 0;
                unite = true;
                break;
              } else {
                break;
              }
            }
            unites.push_back(unite);
          }
        }
      }
    } else if (direction == kLeft) {
      for (int i = 0; i < n; ++i) {
        vector<bool> unites(1);
        for (int j = 0; j < n; ++j) {
          if (next_board[i][j] > 0) {
            bool unite = false;
            for (int next_j = j; next_j > 0; --next_j) {
              if (next_board[i][next_j - 1] == 0) {
                next_board[i][next_j - 1] = next_board[i][next_j];
                next_board[i][next_j] = 0;
              } else if (next_board[i][next_j] == next_board[i][next_j - 1] &&
                         !unites.back()) {
                next_board[i][next_j - 1] *= 2;
                next_board[i][next_j] = 0;
                unite = true;
                break;
              } else {
                break;
              }
            }
            unites.push_back(unite);
          }
        }
      }
    } else {
      for (int i = 0; i < n; ++i) {
        vector<bool> unites(1);
        for (int j = n - 1; j >= 0; --j) {
          if (next_board[i][j] > 0) {
            bool unite = false;
            for (int next_j = j; next_j < n - 1; ++next_j) {
              if (next_board[i][next_j + 1] == 0) {
                next_board[i][next_j + 1] = next_board[i][next_j];
                next_board[i][next_j] = 0;
              } else if (next_board[i][next_j] == next_board[i][next_j + 1] &&
                         !unites.back()) {
                next_board[i][next_j + 1] *= 2;
                next_board[i][next_j] = 0;
                unite = true;
                break;
              } else {
                break;
              }
            }
            unites.push_back(unite);
          }
        }
      }
    }

    max_val = max(max_val, DepthFirstSearch(next_board, step + 1));
  }

  return max_val;
}

void Solve() {
  cout << DepthFirstSearch(board, 0) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
