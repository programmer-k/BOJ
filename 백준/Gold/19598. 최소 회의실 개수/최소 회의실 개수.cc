#include <iostream>
#include <queue>
#include <algorithm>
#include <array>
#include <utility>
#include <vector>
#include <functional>
using namespace std;

int n;
array<pair<int, int>, 100'000> meetings;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> meetings[i].first >> meetings[i].second;
}

void Solve() {
  sort(meetings.begin(), meetings.begin() + n);

  priority_queue<int, vector<int>, greater<int>> pq;
  pq.push(meetings[0].second);
  for (int i = 1; i < n; ++i) {
    if (pq.top() <= meetings[i].first)
      pq.pop();
    pq.push(meetings[i].second);
  }

  cout << pq.size() << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}
