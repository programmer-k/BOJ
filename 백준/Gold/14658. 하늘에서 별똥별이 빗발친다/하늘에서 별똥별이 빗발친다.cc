#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int n, m, l, k;
vector<pair<int, int>> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> l >> k;

  arr.resize(k);
  for (int i = 0; i < k; ++i)
    cin >> arr[i].first >> arr[i].second;
}

void Solve() {
  int max_count = 0;
  sort(arr.begin(), arr.end());

  for (int i = 0; i < ssize(arr); ++i) {
    pair<int, int> target(arr[i].first - l, arr[i].second);
    vector<pair<int, int>>::iterator it =
        lower_bound(arr.begin(), arr.end(), target);

    while (it != arr.begin() + i + 1) {
      int count = 0;
      pair<int, int> top_left(it->first, arr[i].second);
      pair<int, int> bottom_right(top_left.first + l, top_left.second + l);

      for (int j = 0; j < ssize(arr); ++j) {
        if (arr[j].first >= top_left.first &&
            arr[j].first <= bottom_right.first &&
            arr[j].second >= top_left.second &&
            arr[j].second <= bottom_right.second) {
          ++count;
        }
      }

      max_count = max(max_count, count);
      ++it;
    }
  }

  cout << k - max_count << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
