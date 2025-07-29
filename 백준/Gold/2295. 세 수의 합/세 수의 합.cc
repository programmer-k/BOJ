#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

int n;
vector<int> arr;
unordered_set<int> s;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  arr.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
    //s.insert(arr[i]);
  }
}

void Solve() {
  sort(arr.begin(), arr.end());

  int max_val = 0;
  for (int x = 0; x < n; ++x) {
    for (int y = x; y < n; ++y) {
      int total1 = arr[x] + arr[y];
      int k = y + 1;
      for (int z = y; z < n; ++z) {
        int total2 = total1 + arr[z];

        /*if (s.contains(total2)) {
          max_val = max(max_val, total2);
        }*/
        /*if (binary_search(arr.begin() + z + 1, arr.end(), total2)) {
          max_val = max(max_val, total2);
        }*/
        while (k < n && arr[k] < total2) {
          ++k;
        }

        if (k != n && arr[k] == total2)
          max_val = max(max_val, arr[k]);
      }
    }
  }

  cout << max_val << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}