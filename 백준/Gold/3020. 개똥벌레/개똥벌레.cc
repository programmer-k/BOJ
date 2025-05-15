#include <iostream>
#include <array>
using namespace std;

int n, h;
array<int, 200'000> arr;
array<int, 500'001> bottoms, tops;
array<int, 500'001> totals;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> h;
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void Solve() {
  bottoms.fill(0);
  tops.fill(0);
  for (int i = 0; i < n; ++i) {
    int val = arr[i];
    if (i % 2 == 0) {
      ++bottoms[val];
    } else {
      ++tops[val];
    }
  }

  for (int i = h; i > 0; --i) {
    bottoms[i - 1] += bottoms[i];
    tops[i - 1] += tops[i];
  }

  for (int i = 1; i <= h; ++i) {
    totals[i] = bottoms[i] + tops[h + 1 - i];
  }

  /*for (int i = 1; i < h; ++i) {
    cout << totals[i] << ' ';
  }
  cout << '\n';*/

  int min_val = 1234567890;
  int min_count = -1;
  for (int i = 1; i <= h; ++i) {
    if (min_val > totals[i]) {
      min_val = totals[i];
      min_count = 1;
    } else if (min_val == totals[i]) {
      ++min_count;
    }
  }

  cout << min_val << ' ' << min_count << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}