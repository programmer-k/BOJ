#include <iostream>
using namespace std;

int n;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
}

int F(int num) {
  int total = 0;
  for (int i = 1; i <= n; ++i)
    if (num % i == 0)
      total += i;
  
  return total;
}

int G(int num) {
  int total = 0;
  for (int i = 1; i <= n; ++i)
    total += F(i);
  return total;
}

int64_t Calc(int num) {
  int64_t total = 0;
  for (int i = 1; i <= n; ++i) {
    total += num / i * i;
  }
  return total;
}

void Solve() {
  cout << Calc(n) << '\n';
  //cout << G(n) << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}