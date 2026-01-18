#include <cstdint>
#include <iostream>
using namespace std;

int n, m;
int arr[10'000];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  for (int i = 0; i < m; ++i)
    cin >> arr[i];
}

int64_t CountRideNum(int64_t t) {
  int64_t total = m;
  for (int i = 0; i < m; ++i)
    total += t / arr[i];
  return total;
}

void Solve() {
  int64_t low = 0;
  int64_t high = 60'000'000'000;

  if (n <= m) {
    cout << n << '\n';
    return;
  }

  while (low < high) {
    int64_t mid = (low + high) / 2;

    if (CountRideNum(mid) < n)
      low = mid + 1;
    else
      high = mid;
  }

  int64_t prev_ride_num = CountRideNum(low - 1);
  for (int i = 0; i < m; ++i)
    if (low % arr[i] == 0)
      if (++prev_ride_num == n)
        cout << i + 1 << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
