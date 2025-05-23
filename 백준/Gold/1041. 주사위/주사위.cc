#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
using namespace std;

int n;
array<int, 6> dice;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < 6; ++i)
    cin >> dice[i];
}

int GetMinThreeFace() {
  int a = dice[0];
  int b = dice[1];
  int c = dice[2];
  int d = dice[3];
  int e = dice[4];
  int f = dice[5];
  return min({ a + e + d, a + d + b, a + b + c, a + c + e, f + e + d, f + d + b, f + b + c, f + c + e });
}

int GetMinTwoFace() {
  int a = dice[0];
  int b = dice[1];
  int c = dice[2];
  int d = dice[3];
  int e = dice[4];
  int f = dice[5];
  return min({ a + e, a + d, a + b, a + c, e + d, d + b, b + c, c + e, f + e, f + d, f + b, f + c });
}

void Solve() {
  if (n == 1) {
    cout << accumulate(dice.begin(), dice.end(), 0) - *max_element(dice.begin(), dice.end()) << '\n';
    return;
  }

  int min_three_face = GetMinThreeFace();
  int min_two_face = GetMinTwoFace();
  int min_one_face = *min_element(dice.begin(), dice.end());
  cout << min_three_face * 4 + min_two_face * ((2 * n - 3) * 4) + min_one_face * ((n - 2ll) * (n - 1) * 4 + (n - 2ll) * (n - 2)) << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}