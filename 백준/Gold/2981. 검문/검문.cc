#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int n;
array<int, 100> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void Solve() {
  sort(arr.begin(), arr.begin() + n);

  vector<int> diffs;
  for (int i = 1; i < n; ++i)
    diffs.push_back(arr[i] - arr[i - 1]);

  int greatest_common_divisor = diffs[0];
  for (int i = 1; i < ssize(diffs); ++i)
    greatest_common_divisor = gcd(greatest_common_divisor, diffs[i]);

  for (int i = 2; i <= greatest_common_divisor; ++i)
    if (greatest_common_divisor % i == 0)
      cout << i << ' ';
  cout << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}