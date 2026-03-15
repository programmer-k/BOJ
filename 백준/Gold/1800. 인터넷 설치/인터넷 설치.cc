#include <deque>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

const int kIntMax = numeric_limits<int>::max();

int n, p, k;
vector<pair<int, int>> edges[1'001];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> p >> k;

  for (int i = 0; i < p; ++i) {
    int num1, num2, cost;
    cin >> num1 >> num2 >> cost;
    edges[num1].push_back({num2, cost});
    edges[num2].push_back({num1, cost});
  }
}

bool CanAchieve(int x) {
  vector<int> dist(n + 1, kIntMax);
  deque<int> dq;
  dist[1] = 0;
  dq.push_back(1);

  while (!dq.empty()) {
    int cur = dq.front();
    dq.pop_front();

    for (auto [next, cost] : edges[cur]) {
      int w = (cost > x) ? 1 : 0;
      if (dist[cur] + w < dist[next]) {
        dist[next] = dist[cur] + w;
        if (w == 0)
          dq.push_front(next);
        else
          dq.push_back(next);
      }
    }
  }

  return dist[n] <= k;
}

void Solve() {
  int lo = 0, hi = 1'000'000, ans = -1;

  if (!CanAchieve(hi)) {
    cout << -1 << '\n';
    return;
  }

  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (CanAchieve(mid)) {
      ans = mid;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }

  cout << ans << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
