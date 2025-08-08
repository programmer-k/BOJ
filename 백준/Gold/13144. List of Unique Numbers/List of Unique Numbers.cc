#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdint>
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
  int64_t total = static_cast<int64_t>(n) * (n + 1) / 2;
  int last_index = -1;
  unordered_map<int, int> map;
  for (int i = 0; i < n; ++i) {
    if (map.contains(arr[i])) {
      if (map[arr[i]] > last_index) {
        total -= static_cast<int64_t>(n - i) * (map[arr[i]] - last_index);
        last_index = map[arr[i]];
      }

      map.erase(arr[i]);
    }

    map.insert({ arr[i], i });
  }

  cout << total << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}