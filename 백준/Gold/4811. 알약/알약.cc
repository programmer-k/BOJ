#include <iostream>
#include <vector>
#include <stdint.h>
using namespace std;

vector<int> inputs;
vector<vector<int64_t>> dp(31, vector<int64_t>(31));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  while (true) {
    int num;
    cin >> num;
    
    if (num == 0)
      break;
    
    inputs.push_back(num);
  }
}

int64_t CalculateCases(int w, int h) {
  if (w == 0 && h == 0)
    return 1;
  if (dp[w][h] != 0)
    return dp[w][h];

  int64_t total = 0;

  if (w > 0)
    total += CalculateCases(w - 1, h + 1);
  if (h > 0)
    total += CalculateCases(w, h - 1);

  return dp[w][h] = total;
}

void Calculate() {
  CalculateCases(30, 0);
}

void Solve() {
  for (int num : inputs)
    cout << dp[num][0] << '\n';
}

int main(void) {
  Calculate();
  GetInput();
  Solve();
  return 0;
}