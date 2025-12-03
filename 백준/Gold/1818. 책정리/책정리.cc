#include <algorithm>
#include <iostream>
#include <vector>
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
  vector<int> lis;
  for (int i = 0; i < n; ++i) {
    int index = lower_bound(lis.begin(), lis.end(), arr[i]) - lis.begin();
    if (index < ssize(lis))
      lis[index] = arr[i];
    else
      lis.push_back(arr[i]);
  }

  cout << ssize(arr) - ssize(lis) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
