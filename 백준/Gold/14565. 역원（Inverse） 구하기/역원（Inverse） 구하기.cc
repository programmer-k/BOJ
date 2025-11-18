#include <cstdint>
#include <iostream>
#include <numeric>
using namespace std;

int64_t n, a;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n >> a;
}

int64_t ExtendedGCD(int64_t a, int64_t b, int64_t& x, int64_t& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }

  int64_t x1, y1;
  int64_t g = ExtendedGCD(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return g;
}

void Solve() {
  cout << n - a << ' ';

  int64_t x, y, mul_inv;
  int64_t g = ExtendedGCD(a, n, x, y);

  if (g != 1) {
    mul_inv = -1;
  } else {
    x %= n;
    if (x < 0)
      x += n;
    mul_inv = x;
  }

  cout << mul_inv << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
