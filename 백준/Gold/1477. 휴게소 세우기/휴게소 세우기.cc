#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Data {
  int curr_dist;
  int original_dist;
  int ratio;

  bool operator<(const Data& rhs) const {
    return curr_dist < rhs.curr_dist;
  }
};

int n, m, l;
vector<int> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> l;

  arr.resize(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> arr[i];
}

void Solve() {
  vector<int> dists;

  arr.push_back(l);
  sort(arr.begin(), arr.end());
  for (int i = 1; i < ssize(arr); ++i)
    dists.push_back(arr[i] - arr[i - 1]);

  priority_queue<Data> pq;
  for (int dist : dists)
    pq.push({ dist, dist, 1 });

  for (int i = 0; i < m; ++i) {
    Data data = pq.top();
    pq.pop();

    data.curr_dist = data.original_dist / ++data.ratio;
    if (data.original_dist % data.ratio != 0)
      ++data.curr_dist;
    
    pq.push(data);
  }

  cout << pq.top().curr_dist << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
