#include <iostream>
#include <array>
#include <algorithm>
#include <limits>
using namespace std;

int n, m;
array<int, 100'000> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void Solve() {
  int left = 0;
  int right = 0;
  int answer = numeric_limits<int>::max();
  
  sort(arr.begin(), arr.begin() + n);
  while (left < n && right < n) {
    int diff = arr[right] - arr[left];
    if (diff >= m) {
      answer = min(answer, diff);
      ++left;
    } else
      ++right;
  }

  cout << answer << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}