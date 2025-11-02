#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

const int kMod = 1'000'000'007;

int n;
vector<int> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  arr.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

int Power(int base, int exponent) {
  if (exponent == 0)
    return 1;

  int64_t half = Power(base, exponent / 2);
  if (exponent % 2 == 0)
    return half * half % kMod;
  else
    return half * half * base % kMod;
}

void Solve() {
  sort(arr.begin(), arr.end());

  int64_t answer = 0;
  for (int i = 0; i < n; ++i) {
    int64_t count = Power(2, n - 1 - i);
    int diff = arr[n - 1 - i] - arr[i];
    answer += count * diff;
    answer %= kMod;
    if (answer < 0)
      answer += kMod;
  }

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
