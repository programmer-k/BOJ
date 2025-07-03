#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <iterator>
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

  set<int> answers;
  for (int i = 1; i * i <= greatest_common_divisor; ++i)
    if (greatest_common_divisor % i == 0) {
      answers.insert(i);
      answers.insert(greatest_common_divisor / i);
    }

  for (set<int>::iterator it = next(answers.begin()); it != answers.end(); ++it)
    cout << *it << ' ';
  cout << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}