#include <cstdint>
#include <iostream>
using namespace std;

int64_t n;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n;
}

void Solve() {
  if (n % 5 == 0 || n % 5 == 2)
    cout << "CY\n";
  else
    cout << "SK\n";
}

int main() {
  GetInput();
  Solve();
  return 0;
}
