#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;

struct Interval {
  pair<int, int> from;
  pair<int, int> to;

  bool operator<(const Interval& rhs) const {
    if (to == rhs.to)
      return from > rhs.from;
    return to < rhs.to;
  }
};

int n;
vector<Interval> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  for (int i = 0; i < n; ++i) {
    int start_month, start_day, end_month, end_day;
    cin >> start_month >> start_day >> end_month >> end_day;
    
    if (end_month >= 3)
      arr.push_back({{ start_month, start_day }, { end_month, end_day }});
  }
}

void Solve() {
  sort(arr.begin(), arr.end());

  priority_queue<Interval> pq;
  for (const Interval& interval : arr) {
    if (!pq.empty() && pq.top().to < interval.from)
      continue;

    while (!pq.empty()) {
      Interval top = pq.top();
      pq.pop();

      if (!((!pq.empty() && interval.from <= pq.top().to) || (pq.empty() && interval.from <= make_pair(3, 1)))) {
        pq.push(top);
        break;
      }
    }

    pq.push(interval);
  }

  int total = ssize(pq);
  int count1 = 0;
  int count2 = 0;
  while (!pq.empty()) {
    if (pq.top().to.first >= 12)
      ++count1;

    if (pq.top().from <= make_pair(3, 1))
      ++count2;
    pq.pop();
  }

  if (count1 == 0 || count2 == 0) {
    cout << "0\n";
    return;
  }

  cout << total - (count1 - 1) - (count2 - 1) << endl;
}

int main() {
  GetInput();
  Solve();
  return 0;
}
