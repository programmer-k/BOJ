#include <iostream>
#include <array>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

int n;
array<int, 500'000> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void Solve() {
  int total = 0;
  for (int i = 0; i < n; ++i) {
    total += arr[i];
  }
  cout << static_cast<int>(round(static_cast<double>(total) / n)) << '\n';

  sort(arr.begin(), arr.begin() + n);
  cout << arr[n / 2] << '\n';

  map<int, int> m;
  for (int i = 0; i < n; ++i) {
    ++m[arr[i]];
  }

  int max_count = 0;
  for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {
    max_count = max(max_count, it->second);
  }

  int smallest = -1234567890;
  int second_smallest = -1234567890;
  for (map<int, int>::reverse_iterator it = m.rbegin(); it != m.rend(); ++it) {
    if (it->second == max_count) {
      second_smallest = smallest;
      smallest = it->first;
    }
  }

  cout << (second_smallest == -1234567890 ? smallest : second_smallest) << '\n';
  cout << arr[n - 1] - arr[0] << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}