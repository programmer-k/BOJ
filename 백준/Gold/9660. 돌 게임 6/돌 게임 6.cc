#include <iostream>
#include <cstdint>
#include <array>
using namespace std;

int64_t n;
array<bool, 7> arr;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
}

void Solve() {
  arr[0] = false;
  arr[1] = true;
  arr[2] = false;
  arr[3] = arr[4] = arr[5] = arr[6] = true;

  if (arr[n % 7])
    cout << "SK\n";
  else
    cout << "CY\n";
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}