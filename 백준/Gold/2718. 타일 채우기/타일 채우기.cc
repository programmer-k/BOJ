#include <iostream>
#include <vector>
using namespace std;

int t, n;
int dp[101][16];

void GetInput1() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> t;
}

void GetInput2() {
  cin >> n;
}

void Solve() {
  cout << dp[n][0] << '\n';
}

void GenerateNextState(int current_mask, int next_mask, int row,
                       vector<int>& valid_next_masks) {
  if (row == 4) {
    valid_next_masks.push_back(next_mask);
    return;
  }

  if (current_mask & (1 << row)) {
    GenerateNextState(current_mask, next_mask, row + 1, valid_next_masks);
  } else {
    GenerateNextState(current_mask | (1 << row), next_mask | (1 << row),
                      row + 1, valid_next_masks);

    if (row + 1 < 4 && !(current_mask & (1 << (row + 1))))
      GenerateNextState(current_mask | (1 << row) | (1 << (row + 1)), next_mask,
                        row + 2, valid_next_masks);
  }
}

void Calculate() {
  dp[0][0] = 1;

  for (int i = 0; i < 100; ++i) {
    for (int state = 0; state < 16; ++state) {
      if (dp[i][state] == 0)
        continue;

      vector<int> next_states;
      GenerateNextState(state, 0, 0, next_states);

      for (int next_state : next_states)
        dp[i + 1][next_state] += dp[i][state];
    }
  }
}

int main() {
  Calculate();
  GetInput1();
  for (int i = 0; i < t; ++i) {
    GetInput2();
    Solve();
  }
  return 0;
}
