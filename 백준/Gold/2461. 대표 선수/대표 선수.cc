#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> classes(1'000, vector<int>(1'000));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> classes[i][j];
}

void Solve() {
  for (int i = 0; i < n; ++i)
    sort(classes[i].begin(), classes[i].begin() + m);

  int max_val = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  for (int i = 0; i < n; ++i) {
    pq.push({classes[i][0], i});
    max_val = max(max_val, classes[i][0]);
  }

  int answer = numeric_limits<int>::max();
  vector<int> progress(n, 1);
  while (true) {
    pair<int, int> p = pq.top();
    int min_val = p.first;
    int index = p.second;
    pq.pop();

    answer = min(answer, max_val - min_val);

    if (progress[index] >= m)
      break;

    pq.push({classes[index][progress[index]], index});
    max_val = max(max_val, classes[index][progress[index]]);
    ++progress[index];
  }

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
