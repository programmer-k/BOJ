#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<bool> is_primes(1'000'001, true);
vector<int> primes;
vector<int> answers;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n;
}

bool FindFourPrimeNumbers(int num, int depth) {
  if (depth == 3) {
    if (is_primes[num]) {
      answers.push_back(num);
      return true;
    }
    return false;
  }

  int limit = lower_bound(primes.begin(), primes.end(), num) - primes.begin();
  for (int i = limit - 1; i >= 0; --i) {
    if (FindFourPrimeNumbers(num - primes[i], depth + 1)) {
      answers.push_back(primes[i]);
      return true;
    }
  }

  return false;
}

void Solve() {
  is_primes[0] = is_primes[1] = false;
  for (int i = 2; i <= 1'000'000; ++i)
    if (is_primes[i])
      for (int j = i * 2; j <= 1'000'000; j += i)
        is_primes[j] = false;

  for (int i = 0; i <= 1'000'000; ++i)
    if (is_primes[i])
      primes.push_back(i);

  if (FindFourPrimeNumbers(n, 0)) {
    for (int answer : answers)
      cout << answer << ' ';
    cout << '\n';
  } else {
    cout << "-1\n";
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
