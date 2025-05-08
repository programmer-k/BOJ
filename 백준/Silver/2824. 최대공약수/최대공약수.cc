#include <iostream>
#include <array>
#include <numeric>
#include <string>
using namespace std;

int n, m;
array<int, 1'000> arr1, arr2;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> arr1[i];
  
  cin >> m;
  for (int i = 0; i < m; ++i)
    cin >> arr2[i];
}

void Solve() {
  bool is_large_num = false;
  int64_t answer = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int g = gcd(arr1[i], arr2[j]);
      arr1[i] /= g;
      arr2[j] /= g;
      answer *= g;
      if (answer >= 1'000'000'000) {
        answer %= 1'000'000'000;
        is_large_num = true;
      }
    }
  }

  if (is_large_num) {
    for (int i = 0; i < 9 - ssize(to_string(answer)); ++i)
      cout << '0';
    cout << answer << '\n';
  } else
    cout << answer << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}