#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

struct Delivery {
  int from;
  int to;
  int box_count;

  bool operator<(const Delivery& rhs) const {
    return tie(from, to, box_count) < tie(rhs.from, rhs.to, rhs.box_count);
  }

  bool operator>(const Delivery& rhs) const {
    return rhs < *this;
  }
};

int n, c, m;
Delivery deliveries[10'000];
int delivery_info[2'001];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> c;
  cin >> m;

  for (int i = 0; i < m; ++i)
    cin >> deliveries[i].from >> deliveries[i].to >> deliveries[i].box_count;
}

void Solve() {
  sort(deliveries, deliveries + m);

  int prev_from = 0;
  int current_box_count = 0;
  int total_box_count = 0;
  priority_queue<pair<int, int>> pq;

  for (int i = 0; i < m; ++i) {
    int from = deliveries[i].from;
    int to = deliveries[i].to;
    int box_count = deliveries[i].box_count;

    // Unload boxes as we have already reached from.
    for (int visited = prev_from + 1; visited <= from; ++visited)
      current_box_count -= delivery_info[visited];

    int add_up = min(current_box_count + box_count, c) - current_box_count;
    int remaining = box_count - add_up;

    while (!pq.empty() && to < pq.top().first) {
      int val = pq.top().second;
      if (remaining >= val) {
        add_up += val;
        delivery_info[pq.top().first] -= val;
        total_box_count -= val;
        current_box_count -= val;
      } else {
        add_up += remaining;
        pair<int, int> temp = pq.top();
        pq.pop();
        delivery_info[temp.first] -= remaining;
        total_box_count -= remaining;
        current_box_count -= remaining;
        temp.second -= remaining;
        pq.push(temp);
        break;
      }
      pq.pop();
    }

    pq.push({to, add_up});

    delivery_info[to] += add_up;
    current_box_count += add_up;
    total_box_count += add_up;

    prev_from = from;
  }

  cout << total_box_count << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
