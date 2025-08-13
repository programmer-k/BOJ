#include <iostream>
#include <cstdint>
using namespace std;

int x1, x2, x3, x4;
int y1, y2, y3, y4;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> x1 >> y1 >> x2 >> y2;
  cin >> x3 >> y3 >> x4 >> y4;
}

int CounterClockWise(int64_t x1, int64_t y1, int64_t x2, int64_t y2, int64_t x3, int64_t y3) {
  return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1) > 0 ? 1 : -1;
}

void Solve() {
  int ret1 = CounterClockWise(x1, y1, x2, y2, x3, y3);
  int ret2 = CounterClockWise(x1, y1, x2, y2, x4, y4);
  int ret3 = CounterClockWise(x3, y3, x4, y4, x1, y1);
  int ret4 = CounterClockWise(x3, y3, x4, y4, x2, y2);

  if (ret1 * ret2 == -1 && ret3 * ret4 == -1)
    cout << "1\n";
  else
    cout << "0\n";
}

int main() {
  GetInput();
  Solve();
  return 0;
}
