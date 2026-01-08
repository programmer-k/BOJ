#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;

int n, c;
int arr[30];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> c;

  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void CountAllCases(int index, int end, int64_t total, map<int64_t, int>& m) {
  if (index > end) {
    ++m[total];
    return;
  }

  CountAllCases(index + 1, end, total, m);
  CountAllCases(index + 1, end, total + arr[index], m);
}

void Solve() {
  int mid = n / 2;
  map<int64_t, int> m1, m2;
  CountAllCases(0, mid, 0, m1);
  CountAllCases(mid + 1, n - 1, 0, m2);

  vector<pair<int64_t, int>> v1(m1.begin(), m1.end());
  vector<pair<int64_t, int>> v2(m2.begin(), m2.end());
  vector<int> v2_prefix_sum(ssize(v2));

  v2_prefix_sum[0] = v2[0].second;
  for (int i = 1; i < ssize(v2); ++i)
    v2_prefix_sum[i] = v2_prefix_sum[i - 1] + v2[i].second;

  int answer = 0;
  for (const pair<int64_t, int>& p : v1) {
    int64_t sum1 = p.first;
    int count1 = p.second;
    int64_t sum2 = c - sum1;

    int index =
        upper_bound(v2.begin(), v2.end(), make_pair(sum2 + 1, 0)) - v2.begin();

    if (index > 0)
      answer += count1 * v2_prefix_sum[index - 1];
  }

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
