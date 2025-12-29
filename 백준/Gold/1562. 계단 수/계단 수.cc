#include <iostream>
using namespace std;

int n;
int dp[101][10][1'024];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n;
}

void Solve() {
  // Initialize the dp table.
  for (int j = 1; j <= 9; ++j)
    dp[1][j][1 << j] = 1;

  // Calculate the dp table.
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j <= 9; ++j) {
      for (int k = 0; k < 1024; ++k) {
        if (j >= 1) {
          dp[i + 1][j - 1][k | (1 << (j - 1))] += dp[i][j][k];
          dp[i + 1][j - 1][k | (1 << (j - 1))] %= 1'000'000'000;
        }

        if (j <= 8) {
          dp[i + 1][j + 1][k | (1 << (j + 1))] += dp[i][j][k];
          dp[i + 1][j + 1][k | (1 << (j + 1))] %= 1'000'000'000;
        }
      }
    }
  }

  // Calculate the answer from the dp table.
  int answer = 0;
  for (int j = 0; j <= 9; ++j) {
    answer += dp[n][j][1023];
    answer %= 1'000'000'000;
  }

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
