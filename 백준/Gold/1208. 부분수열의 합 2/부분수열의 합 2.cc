#include <cstdint>
#include <iostream>
#include <map>
using namespace std;

int n, s;
int arr[40];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> s;

  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void CalculateAllSums(map<int, int>& m, int i, int sum, int from, int to) {
  if (i == to) {
    ++m[sum];
    return;
  }

  CalculateAllSums(m, i + 1, sum, from, to);
  CalculateAllSums(m, i + 1, arr[i] + sum, from, to);
}

void Solve() {
  int mid = n / 2;
  map<int, int> left_map, right_map;

  CalculateAllSums(left_map, 0, 0, 0, mid);
  CalculateAllSums(right_map, mid, 0, mid, n);

  int64_t answer = 0;
  for (const pair<const int, int>& p : left_map)
    if (right_map.contains(s - p.first))
      answer += static_cast<int64_t>(p.second) * right_map[s - p.first];

  cout << (s == 0 ? answer - 1 : answer) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
