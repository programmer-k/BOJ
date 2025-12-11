#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int n;
vector<pair<int, int>> coordinates;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  coordinates.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> coordinates[i].first >> coordinates[i].second;
}

int CalculateMax(const vector<pair<int, int>>& lines) {
  int max_count = 0;
  priority_queue<int, vector<int>, greater<int>> pq;

  for (int i = 0; i < ssize(lines); ++i) {
    while (!pq.empty() && pq.top() <= lines[i].first)
      pq.pop();

    pq.push(lines[i].second);
    max_count = max(max_count, static_cast<int>(ssize(pq)));
  }

  return max_count;
}

void Solve() {
  vector<pair<int, int>> horizontal_lines, vertical_lines;
  for (int i = 1; i <= n; ++i) {
    const pair<int, int>& prev = coordinates[i - 1];
    const pair<int, int>& curr = coordinates[i % n];

    int horizontal_min = min(prev.first, curr.first);
    int horizontal_max = max(prev.first, curr.first);
    int vertical_min = min(prev.second, curr.second);
    int vertical_max = max(prev.second, curr.second);

    if (prev.second == curr.second)
      horizontal_lines.push_back({horizontal_min, horizontal_max});
    else
      vertical_lines.push_back({vertical_min, vertical_max});
  }

  sort(horizontal_lines.begin(), horizontal_lines.end());
  sort(vertical_lines.begin(), vertical_lines.end());

  int answer1 = CalculateMax(horizontal_lines);
  int answer2 = CalculateMax(vertical_lines);
  cout << max(answer1, answer2) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
