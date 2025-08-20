#include <iostream>
#include <algorithm>
using namespace std;

int n, m, x, y, k;
int map[20][20];
int commands[1000];
int dice_nums[7]; // empty, up, down, front, back, left, right

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> x >> y >> k;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> map[i][j];
  
  for (int i = 0; i < k; ++i)
    cin >> commands[i];
}

bool Move(int direction) {
  // Out of range
  int move_row[5] = { 0, 0, 0, -1, 1 };
  int move_col[5] = { 0, 1, -1, 0, 0 };
  int next_row = x + move_row[direction];
  int next_col = y + move_col[direction];

  if (next_row < 0 || next_col < 0 || next_row >= n || next_col >= m)
    return false;

  // Move map position
  x = next_row;
  y = next_col;

  // Move dice
  int dice_nums_copy[7];
  copy(dice_nums, dice_nums + 7, dice_nums_copy);
  if (direction == 1) {
    dice_nums[1] = dice_nums_copy[5];
    dice_nums[2] = dice_nums_copy[6];
    dice_nums[5] = dice_nums_copy[2];
    dice_nums[6] = dice_nums_copy[1];
  } else if (direction == 2) {
    dice_nums[1] = dice_nums_copy[6];
    dice_nums[2] = dice_nums_copy[5];
    dice_nums[5] = dice_nums_copy[1];
    dice_nums[6] = dice_nums_copy[2];
  } else if (direction == 3) {
    dice_nums[1] = dice_nums_copy[3];
    dice_nums[2] = dice_nums_copy[4];
    dice_nums[3] = dice_nums_copy[2];
    dice_nums[4] = dice_nums_copy[1];
  } else {
    dice_nums[1] = dice_nums_copy[4];
    dice_nums[2] = dice_nums_copy[3];
    dice_nums[3] = dice_nums_copy[1];
    dice_nums[4] = dice_nums_copy[2];
  }

  int& val = map[x][y];
  if (val == 0) {
    val = dice_nums[2]; 
  } else {
    dice_nums[2] = val;
    val = 0;
  }

  return true;
}

void Solve() {
  for (int i = 0; i < k; ++i)
    if (Move(commands[i]))
      cout << dice_nums[1] << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}