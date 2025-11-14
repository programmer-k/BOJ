#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int r, c;
vector<vector<char>> map(27, vector<char>(27));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> r >> c;
  for (int i = 1; i <= r; ++i)
    for (int j = 1; j <= c; ++j)
      cin >> map[i][j];
}

void Solve() {
  for (int i = 1; i <= r; ++i) {
    for (int j = 1; j <= c; ++j) {
      char val = map[i][j];

      if (val != '.')
        continue;

      char up_val = map[i - 1][j];
      bool is_up = false;
      if (up_val == '|' || up_val == '+' || up_val == '1' || up_val == '4')
        is_up = true;

      char down_val = map[i + 1][j];
      bool is_down = false;
      if (down_val == '|' || down_val == '+' || down_val == '2' ||
          down_val == '3')
        is_down = true;

      char left_val = map[i][j - 1];
      bool is_left = false;
      if (left_val == '-' || left_val == '+' || left_val == '1' ||
          left_val == '2')
        is_left = true;

      char right_val = map[i][j + 1];
      bool is_right = false;
      if (right_val == '-' || right_val == '+' || right_val == '3' ||
          right_val == '4')
        is_right = true;

      char answer = 'N';
      if (is_up && is_down && is_left && is_right)
        answer = '+';
      else if (is_up && is_down)
        answer = '|';
      else if (is_left && is_right)
        answer = '-';
      else if (is_down && is_right)
        answer = '1';
      else if (is_up && is_right)
        answer = '2';
      else if (is_up && is_left)
        answer = '3';
      else if (is_down && is_left)
        answer = '4';

      if (answer != 'N') {
        cout << i << ' ' << j << ' ' << answer << '\n';
        return;
      }
    }
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
