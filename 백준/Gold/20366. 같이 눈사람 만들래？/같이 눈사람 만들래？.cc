#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

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

void Solve() {
  sort(arr.begin(), arr.end());

  int min_val = numeric_limits<int>::max();
  for (int i = 0; i < n; ++i) {
    for (int j = i + 3; j < n; ++j) {
      int sum1 = arr[i] + arr[j];
      int left = i + 1;
      int right = j - 1;

      while (left < right) {
        int sum2 = arr[left] + arr[right];
        min_val = min(min_val, abs(sum1 - sum2));

        if (sum2 < sum1)
          ++left;
        else
          --right;
      }
    }
  }

  cout << min_val << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
