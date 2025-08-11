#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

const int x = 1'000'000'007;
int m;
vector<int> n, s;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> m;

  n.resize(m);
  s.resize(m);
  for (int i = 0; i < m; ++i)
    cin >> n[i] >> s[i];
}

int64_t Square(int64_t val) {
  return val * val;
}

int64_t Power(int base, int exp, int mod) {
  if (exp == 0)
    return 1;
  
  if (exp % 2 == 0)
    return Square(Power(base, exp / 2, mod)) % mod;
  
  return Power(base, exp - 1, mod) * base % mod;
}

void Solve() {
  int64_t q = 0;
  for (int i = 0; i < m; ++i)
    q += s[i] * Power(n[i], x - 2, x) % x;
  
  cout << q % x << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
