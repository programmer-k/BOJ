#include <cstdint>
#include <iostream>
using namespace std;

struct Matrix {
  int64_t a;
  int64_t b;
  int64_t c;
  int64_t d;

  Matrix operator*(const Matrix& rhs) {
    int64_t a = (this->a * rhs.a + this->b * rhs.c) % 1'000'000'000;
    int64_t b = (this->a * rhs.b + this->b * rhs.d) % 1'000'000'000;
    int64_t c = (this->c * rhs.a + this->d * rhs.c) % 1'000'000'000;
    int64_t d = (this->c * rhs.b + this->d * rhs.d) % 1'000'000'000;

    return Matrix(a, b, c, d);
  }
};

int64_t a, b;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> a >> b;
}

Matrix Power(const Matrix& mat, int64_t exponent) {
  if (exponent == 1)
    return mat;

  int64_t half = exponent / 2;
  Matrix half_val = Power(mat, half);
  if (exponent % 2 == 0)
    return half_val * half_val;
  else
    return half_val * half_val * mat;
}

void Solve() {
  Matrix mat = {1, 1, 1, 0};
  int64_t val = Power(mat, b + 2).c - Power(mat, a + 1).c;

  if (val < 0)
    val += 1'000'000'000;

  cout << val << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
