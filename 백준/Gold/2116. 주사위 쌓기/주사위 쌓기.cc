#include <iostream>
#include <array>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int n;
array<array<int, 6>, 10'000> dices;
map<int, int> m;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < 6; ++j)
      cin >> dices[i][j];
}

int GetMaxValue(int dice_index, int top_index) {
  int bottom_index = m[top_index];
  vector<int> vec;

  for (int i = 0; i < 6; ++i)
    if (i != top_index && i != bottom_index)
      vec.push_back(dices[dice_index][i]);

  return *max_element(vec.begin(), vec.end());
}

int GetBottomIndex(int dice_index, int top_value) {
  for (int i = 0; i < 6; ++i)
    if (dices[dice_index][i] == top_value)
      return i;
  return -1;
}

void Solve() {
  int max_val = 0;
  m[0] = 5;
  m[1] = 3;
  m[2] = 4;
  m[3] = 1;
  m[4] = 2;
  m[5] = 0;

  for (int i = 0; i < 6; ++i) {
    int total = GetMaxValue(0, i);
    int prev_top_val = dices[0][i];

    for (int j = 1; j < n; ++j) {
      int bottom_index = GetBottomIndex(j, prev_top_val);
      int top_index = m[bottom_index];
      total += GetMaxValue(j, top_index);
      prev_top_val = dices[j][top_index];
    }

    max_val = max(max_val, total);
  }

  cout << max_val << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}