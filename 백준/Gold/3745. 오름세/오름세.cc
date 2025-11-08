#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> arr(100'000);

void GetInput() {
  arr.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void Solve() {
  vector<int> lis;
  for (int val : arr) {
    vector<int>::iterator it = lower_bound(lis.begin(), lis.end(), val);

    if (it == lis.end())
      lis.push_back(val);
    else
      *it = val;
  }

  cout << lis.size() << '\n';
}

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  while (cin >> n) {
    GetInput();
    Solve();
  }

  return 0;
}
