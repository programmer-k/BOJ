#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int n, s;
vector<pair<int, int>> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> s;

  arr.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> arr[i].first >> arr[i].second;
}

void Solve() {
  unordered_map<int, int> m;
  for (const pair<int, int>& p : arr)
    if (m.contains(p.first))
      m[p.first] = max(m[p.first], p.second);
    else
      m[p.first] = p.second;

  vector<pair<int, int>> pictures;
  for (unordered_map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
    pictures.push_back({it->first, it->second});

  sort(pictures.begin(), pictures.end());

  vector<int> dp(ssize(pictures));
  for (int i = 0; i < ssize(pictures); ++i) {
    int index = lower_bound(pictures.begin(), pictures.end(), make_pair(pictures[i].first - s + 1, 0)) - pictures.begin();
    index -= 1;

    dp[i] = pictures[i].second;

    if (i > 0)
      dp[i] = max(dp[i], dp[i - 1]);
    
    if (index != -1)
      dp[i] = max(dp[i], dp[index] + pictures[i].second);
  }

  cout << dp[ssize(pictures) - 1] << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
