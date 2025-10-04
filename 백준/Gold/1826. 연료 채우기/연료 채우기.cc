#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int n, l, p;
vector<pair<int, int>> stations;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  stations.resize(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> stations[i].first >> stations[i].second;

  cin >> l >> p;
}

void Solve() {
  sort(stations.begin(), stations.end());
  stations.push_back({l, 0});

  int stop_count = 0;
  priority_queue<int> pq;
  for (int i = 1; i < ssize(stations); ++i) {
    int move_forward = stations[i].first - stations[i - 1].first;

    while (p - move_forward < 0 && !pq.empty()) {
      p += pq.top();
      pq.pop();
      ++stop_count;
    }

    if (p - move_forward < 0) {
      stop_count = -1;
      break;
    }

    p -= move_forward;
    pq.push(stations[i].second);
  }

  cout << stop_count << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
