#include <cstdint>
#include <iostream>
using namespace std;

int64_t n, k;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n >> k;
}

int64_t CountLessThanOrEqualTo(int64_t val) {
  int64_t count = 0;
  for (int i = 1; i <= n; ++i)
    count += min(val / i, n);
  return count;
}

void Solve() {
  int64_t left = 1;
  int64_t right = n * n;

  while (left < right) {
    int64_t mid = (left + right) / 2;
    int64_t index = CountLessThanOrEqualTo(mid);

    if (index < k)
      left = mid + 1;
    else
      right = mid;
  }

  cout << left << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
