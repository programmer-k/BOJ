#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  arr.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void Solve() {
  if (n == 2 && arr[0] == arr[1]) {
    cout << arr[0] << '\n';
    return;
  }

  if (n == 1 || n == 2) {
    cout << "A\n";
    return;
  }

  int a = arr[1] - arr[0] ? (arr[2] - arr[1]) / (arr[1] - arr[0]) : 1;
  int b = arr[1] - arr[0] * a;

  for (int i = 0; i < n - 1; ++i) {
    if (arr[i] * a + b != arr[i + 1]) {
      cout << "B\n";
      return;
    }
  }

  cout << arr.back() * a + b << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
