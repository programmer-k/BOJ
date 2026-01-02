#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

int64_t n;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n;
}

vector<int64_t> Factorize(int64_t val) {
  vector<int64_t> factors;

  for (int64_t i = 2; i * i <= val; ++i) {
    if (val % i == 0) {
      factors.push_back(i);
      while (val % i == 0) {
        val /= i;
      }
    }
  }

  if (val > 1)
    factors.push_back(val);

  return factors;
}

void Calculate(int64_t& answer, vector<bool>& selected,
               const vector<int64_t>& factors) {
  if (ssize(selected) == ssize(factors)) {
    int64_t mult = 1;
    int count = 0;
    for (int i = 0; i < ssize(selected); ++i) {
      if (selected[i]) {
        mult *= factors[i];
        ++count;
      }
    }

    if (count == 0)
      return;

    if (count % 2 == 0)
      answer += n / mult;
    else
      answer -= n / mult;

    return;
  }

  selected.push_back(true);
  Calculate(answer, selected, factors);
  selected.pop_back();

  selected.push_back(false);
  Calculate(answer, selected, factors);
  selected.pop_back();
}

void Solve() {
  int64_t answer = n;
  vector<int64_t> factors = Factorize(n);
  vector<bool> selected;

  Calculate(answer, selected, factors);
  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
