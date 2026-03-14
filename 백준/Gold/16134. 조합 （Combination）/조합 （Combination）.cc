#include <cstdint>
#include <iostream>
using namespace std;

const int kMod = 1'000'000'007;

int n, r;
int factorials[1'000'001];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n >> r;
}

void CalculateFactorials() {
  factorials[0] = 1;
  for (int64_t i = 1; i <= 1'000'000; ++i)
    factorials[i] = factorials[i - 1] * i % kMod;
}

int Power(int base, int exp) {
  if (exp == 0)
    return 1;

  int64_t half = Power(base, exp / 2);
  if (exp % 2 == 0)
    return half * half % kMod;
  else
    return half * half % kMod * base % kMod;
}

int Multiply(int64_t val1, int64_t val2, int64_t val3) {
  return val1 * val2 % kMod * val3 % kMod;
}

void Solve() {
  CalculateFactorials();

  // (r!)^(-1) = (r!)^(kMod - 2)
  // ((n - r)!)^(-1) = ((n - r)!)^(kMod - 2)
  int factorial_n = factorials[n];
  int inverse_r_factorial = Power(factorials[r], kMod - 2);
  int inverse_n_minus_r_factorial = Power(factorials[n - r], kMod - 2);
  int answer =
      Multiply(factorial_n, inverse_r_factorial, inverse_n_minus_r_factorial);

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
