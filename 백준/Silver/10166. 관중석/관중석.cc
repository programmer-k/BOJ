#include <iostream>
#include <vector>
using namespace std;

int d1, d2;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> d1 >> d2;
}

void Solve() {
  vector<int> arr(d2 + 1);
  for (int i = 1; i <= d2; ++i) {
    arr[i] = i;
  }

  for (int i = 1; i <= d2; ++i) {
    for (int j = i + i; j <= d2; j += i) {
      arr[j] -= arr[i];
    }
  }

  int total = 0;
  for (int i = 1; i <= d2; ++i)
    total += arr[i];
  cout << total << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}