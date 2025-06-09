#include <iostream>
#include <limits>
#include <numeric>
using namespace std;

int num1, num2;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> num1 >> num2;
}

void Solve() {
  int min_val = numeric_limits<int>::max();
  int answer1 = -1, answer2 = -1;
  int limit = num2 / num1;
  //cout << "limit:" << limit << endl;
  for (int i = 1; i <= limit; ++i) {
    if (limit % i == 0) {
      int val1 = num1 * i;
      int val2 = limit / i * num1;

      //cout << "val1: " << val1 << ", val2: " << val2 << endl;
      if (gcd(val1, val2) == num1 && val1 + val2 < min_val) {
        min_val = val1 + val2;
        answer1 = val1;
        answer2 = val2;
        //cout << "answer1: " << answer1 << ", " << answer2 << endl;
      }
    }
  }

  cout << answer1 << ' ' << answer2 << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}