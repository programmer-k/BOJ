#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

double x1, _y1, r1, x2, y2, r2;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> x1 >> _y1 >> r1 >> x2 >> y2 >> r2;
}

double Square(double val) {
  return val * val;
}

void Solve() {
  double d = sqrt(Square(x1 - x2) + Square(_y1 - y2));
  if (r1 + r2 <= d) {
    cout << fixed << setprecision(3) << static_cast<double>(0.0) << '\n';
  } else if (abs(r1 - r2) >= d) {
    cout << fixed << setprecision(3) << M_PI * Square(min(r1, r2)) << '\n';
  } else {
    double alpha =
        2 * acos((Square(d) + Square(r1) - Square(r2)) / (2 * d * r1));
    double beta =
        2 * acos((Square(d) + Square(r2) - Square(r1)) / (2 * d * r2));
    double s =
        (Square(r1) * (alpha - sin(alpha)) + Square(r2) * (beta - sin(beta))) /
        2;
    cout << fixed << setprecision(3) << s << '\n';
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
