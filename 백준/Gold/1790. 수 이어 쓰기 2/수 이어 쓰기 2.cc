#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
using namespace std;

int n, k;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> k;
}

int64_t Power(int base, int exponent) {
  int64_t val = 1;
  for (int i = 1; i <= exponent; ++i)
    val *= base;
  return val;
}

void Solve() {
  int digit = 1;
  int64_t acc = 0;

  while (true) {
    int64_t start = Power(10, digit - 1);
    int64_t end = Power(10, digit) - 1;

    if (start > n)
      break;
    
    int64_t last = min(static_cast<int64_t>(n), end);
    int64_t num_count = last - start + 1;
    int64_t add = num_count * digit;

    if (acc + add >= k)
      break;

    acc += add;
    ++digit;
  }

  int64_t remain = k - acc - 1;
  int64_t start = Power(10, digit - 1);
  int64_t offset = remain / digit;
  int64_t pos = remain % digit;
  int64_t target = start + offset;

  if (target > n) {
      cout << -1 << '\n';
      return;
  }

  string s = to_string(target);
  cout << s[pos] << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}