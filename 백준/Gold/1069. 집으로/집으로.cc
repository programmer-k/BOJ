#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <limits>
using namespace std;

int x, y, d, t;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> x >> y >> d >> t;
}

void Solve() {
  double candidate1, candidate2, candidate3, candidate4, candidate5;
  candidate1 = sqrt(x * x + y * y);
  
  int quotient = static_cast<int>(candidate1) / d;
  double remainder = candidate1 - d * quotient;
  candidate2 = t * quotient + remainder;
  
  remainder = d * (quotient + 1) - candidate1;
  candidate3 = t * (quotient + 1) + remainder;

  candidate4 = d * 2 > candidate1 ? t * 2 : numeric_limits<double>::infinity();

  candidate5 = quotient > 0 ? t * (quotient + 1) : numeric_limits<double>::infinity();

  cout << fixed << setprecision(10) << min({candidate1, candidate2, candidate3, candidate4, candidate5}) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
