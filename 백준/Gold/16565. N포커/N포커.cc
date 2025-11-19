#include <iostream>
#include <vector>
using namespace std;

const int kMod = 10'007;

int n;
vector<vector<int>> combinations(53, vector<int>(53));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n;
}

void Solve() {
  for (int i = 0; i <= 52; ++i)
    combinations[i][0] = 1;

  for (int i = 1; i <= 52; ++i)
    for (int j = 1; j <= 52; ++j)
      combinations[i][j] =
          (combinations[i - 1][j] + combinations[i - 1][j - 1]) % kMod;

  int answer = 0;
  for (int i = 1; i <= n / 4; ++i) {
    if (i % 2 == 1) {
      answer += (combinations[13][i] * combinations[52 - i * 4][n - i * 4]);
      answer %= kMod;
    } else {
      answer -=
          (combinations[13][i] * combinations[52 - i * 4][n - i * 4]) % kMod;
      answer = (answer + kMod) % kMod;
    }
  }

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
