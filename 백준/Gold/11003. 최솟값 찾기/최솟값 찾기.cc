#include <deque>
#include <iostream>
#include <utility>
using namespace std;

int n, l;
int arr[5'000'000];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> l;

  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void Solve() {
  deque<pair<int, int>> deq;

  for (int i = 0; i < n; ++i) {
    int val = arr[i];

    while (!deq.empty() && val <= deq.back().second)
      deq.pop_back();

    deq.push_back({i, val});

    if (deq.front().first <= i - l)
      deq.pop_front();

    cout << deq.front().second << ' ';
  }
  cout << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
