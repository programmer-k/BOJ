#include <cstdint>
#include <iostream>
using namespace std;

int l, u;
int64_t digit_sums[10];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> l >> u;
}

int64_t Power(int base, int exp) {
  int64_t val = 1;
  for (int i = 0; i < exp; ++i)
    val *= base;
  return val;
}

void InitDigitSums() {
  // digit_sums[0]: sum from 0 to 9.
  // digit_sums[1]: sum from 0 to 99.
  // digit_sums[2]: sum from 0 to 999.
  // ...
  // digit_sums[9]: sum from 0 to 9,999,999,999.
  digit_sums[0] = 45;
  for (int i = 1; i < 10; ++i)
    digit_sums[i] = digit_sums[i - 1] * 10 + digit_sums[0] * Power(10, i);
}

int64_t CalcDigitSum(int num) {
  if (num < 0)
    return 0;
  if (num < 10)
    return static_cast<int64_t>(num) * (num + 1) / 2;

  // Count the number of digits.
  int digits = 0;
  int temp = num;
  while (temp > 0) {
    temp /= 10;
    ++digits;
  }

  int k = digits - 1;        // Number of lower digits.
  int64_t p = Power(10, k);  // 10^k
  int d = num / p;           // Leading digit.
  int rest = num % p;        // Remaining part.

  // d full blocks [0, 10^k), each contributes digit_sums[k-1].
  // Leading digits 0..d-1 each appear 10^k times: sum = d*(d-1)/2 * 10^k.
  // Partial block [d*10^k, num]: d appears (rest+1) times, plus
  // CalcDigitSum(rest).
  return static_cast<int64_t>(d) * digit_sums[k - 1] +
         static_cast<int64_t>(d) * (d - 1) / 2 * p +
         static_cast<int64_t>(d) * (rest + 1) + CalcDigitSum(rest);
}

void Solve() {
  InitDigitSums();

  int64_t a = CalcDigitSum(l - 1);
  int64_t b = CalcDigitSum(u);

  cout << b - a << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
