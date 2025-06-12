#include <iostream>
#include <utility>
#include <array>
#include <algorithm>
using namespace std;

int n, l;
array<pair<int, int>, 10'000> holes;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> l;
  for (int i = 0; i < n; ++i)
    cin >> holes[i].first >> holes[i].second;
}

void Solve() {
  sort(holes.begin(), holes.begin() + n);

  int answer = 0;
  int prev_end = 0;
  for (int i = 0; i < n; ++i) {
    int from = max(holes[i].first, prev_end + 1);
    int to = holes[i].second;
    int dist = to - from;
    int count = 0;

    if (prev_end >= to - 1)
      continue;

    count += dist / l; 

    if (dist % l != 0)
      ++count;

    int end = from + count * l - 1;
    prev_end = end;

    answer += count;
  }

  cout << answer << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}