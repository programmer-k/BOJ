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
  vector<int> pos(n + 1);
  for (int i = 0; i < n; ++i)
    pos[arr[i]] = i;

  int curr_len = 1, max_len = 1;
  for (int val = 1; val < n; ++val)
    if (pos[val] < pos[val + 1])
      max_len = max(max_len, ++curr_len);
    else
      curr_len = 1;

  cout << n - max_len << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
