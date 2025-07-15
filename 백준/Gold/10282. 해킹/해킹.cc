#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
#include <limits>
using namespace std;

int test_case;
int n, d, c;
vector<vector<pair<int, int>>> edges(10'001);

void GetInput1() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> test_case;
}

void GetInput2() {
  for (int i = 1; i <= n; ++i)
    edges[i].clear();

  cin >> n >> d >> c;
  for (int i = 0; i < d; ++i) {
    int a, b, s;
    cin >> a >> b >> s;
    edges[b].push_back({ a, s });
  }
}

bool IsInfected(int val) {
  return val == numeric_limits<int>::max() ? false : true;
}

void Dijkstra() {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  vector<int> dists(n + 1, numeric_limits<int>::max());
  pq.push({ 0, c });
  dists[c] = 0;

  while (!pq.empty()) {
    pair<int, int> p = pq.top();
    int curr_dist = p.first;
    int curr_node = p.second;
    pq.pop();

    if (curr_dist > dists[curr_node])
      continue;
    
    for (pair<int, int> next : edges[curr_node]) {
      int next_node = next.first;
      int next_dist = curr_dist + next.second;

      if (next_dist < dists[next_node]) {
        pq.push({ next_dist, next_node });
        dists[next_node] = next_dist;
      }
    }
  }

  int max_val = 0;
  for (int i = 1; i <= n; ++i)
    if (dists[i] != numeric_limits<int>::max())
      max_val = max(max_val, dists[i]);

  cout << count_if(dists.begin(), dists.end(), IsInfected) << ' ' << max_val << '\n';
}

void Solve() {
  Dijkstra();
}

int main() {
  GetInput1();
  for (int i = 0; i < test_case; ++i) {
    GetInput2();
    Solve();
  }
  return 0;
}