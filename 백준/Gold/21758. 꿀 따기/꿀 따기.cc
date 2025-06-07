#include <iostream>
#include <array>
using namespace std;

int n;
array<int, 100'001> arr, prefix_sum;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> arr[i];
}

void Solve() {
  for (int i = 1; i <= n; ++i)
    prefix_sum[i] = prefix_sum[i - 1] + arr[i];

  int max_val = 0;

  // The hive is on the left.
  for (int i = 2; i <= n - 1; ++i)
    max_val = max(max_val, prefix_sum[i - 1] + (prefix_sum[n - 1] - arr[i]));
  
  // The hive is in the middle.
  for (int i = 2; i <= n - 1; ++i)
    max_val = max(max_val, (prefix_sum[i] - arr[1]) + (prefix_sum[n - 1] - prefix_sum[i - 1]));

  // The hive is on the right.
  for (int i = 2; i <= n - 1; ++i)
    max_val = max(max_val, (prefix_sum[n] - arr[1] - arr[i]) + (prefix_sum[n] - prefix_sum[i]));

  cout << max_val << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}