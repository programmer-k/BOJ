#include <iostream>
#include <iomanip>
using namespace std;

int n;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
}

void Solve() {
  int64_t answer = 1;
  for (int i = 1; i <= n; ++i) {
    answer *= i;
    while (answer % 10 == 0) {
      answer /= 10;
    }
    answer %= 1'000'000'000'000;

    //cout << i << ": " << answer << '\n';
  }

  cout << setfill('0') << setw(5) << answer % 100'000 << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}