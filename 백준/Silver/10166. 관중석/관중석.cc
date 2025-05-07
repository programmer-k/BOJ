#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int d1, d2;
vector<vector<bool>> occupied(2001, vector<bool>(2001));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> d1 >> d2;
}

void Solve() {
  int count = 0;
  for (int i = d1; i <= d2; ++i) {
    for (int j = 0; j < i; ++j) {
      int val = gcd(i, j);
      int numerator = j / val;
      int denominator = i / val;

      if (!occupied[numerator][denominator]) {
        occupied[numerator][denominator] = true;
        ++count;
      }
    }
  }

  cout << count << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}