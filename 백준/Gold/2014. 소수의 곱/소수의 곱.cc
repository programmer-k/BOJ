#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>
#include <limits>
using namespace std;

const int64_t kIntMax = numeric_limits<int>::max();

int k, n;
int arr[100];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> k >> n;

  for (int i = 0; i < k; ++i)
    cin >> arr[i];
}

void Solve() {
  priority_queue<int, vector<int>, greater<int>> pq;

  for (int i = 0; i < k; ++i)
    pq.push(arr[i]);

  int answer = 0;
  for (int i = 0; i < n; ++i) {
    if (pq.top() == answer) {
      pq.pop();
      --i;
      continue;
    }

    answer = pq.top();
    pq.pop();

    for (int j = 0; j < k; ++j)
      if (static_cast<int64_t>(answer) * arr[j] < kIntMax)
        pq.push(answer * arr[j]);
  }

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
