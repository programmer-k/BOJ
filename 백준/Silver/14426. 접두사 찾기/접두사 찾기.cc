#include <iostream>
#include <string>
#include <array>
#include <algorithm>
using namespace std;

int n, m;
array<string, 10'000> arr1, arr2;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> arr1[i];

  for (int i = 0; i < m; ++i)
    cin >> arr2[i];
}

void Solve() {
  int answer = 0;
  sort(arr1.begin(), arr1.begin() + n);
  for (int i = 0; i < m; ++i) {
    if (lower_bound(arr1.begin(), arr1.begin() + n, arr2[i])->starts_with(arr2[i])) {
      ++answer;
    }
  }

  cout << answer << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}