#include <cstdint>
#include <iostream>
using namespace std;

const int kMod = 1'000'000'007;

struct Matrix {
  int64_t a;
  int64_t b;
  int64_t c;
  int64_t d;
};

Matrix operator*(const Matrix& mat1, const Matrix& mat2) {
  return Matrix((mat1.a * mat2.a + mat1.b * mat2.c) % kMod,
                (mat1.a * mat2.b + mat1.b * mat2.d) % kMod,
                (mat1.c * mat2.a + mat1.d * mat2.c) % kMod,
                (mat1.c * mat2.b + mat1.d * mat2.d) % kMod);
}

int64_t n;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n;
}

Matrix Power(Matrix mat, int64_t exponent) {
  if (exponent == 0)
    return Matrix(1, 0, 0, 1);

  Matrix half = Power(mat, exponent / 2);
  Matrix full = half * half;

  if (exponent % 2 == 1)
    full = full * mat;

  return full;
}

void Solve() {
  // n이 홀수일 때, 홀수 번째 피보나치 수의 합은 n + 1 번째 피보나치 수의 합과 동일하다.
  // n이 짝수일 때, 짝수 번째 피보나치 수의 합은 n 번째 피보나치 수의 합과 동일하다.
  if (n % 2 == 1)
    ++n;

  Matrix mat = Power(Matrix(1, 1, 1, 0), n);
  cout << mat.c << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
