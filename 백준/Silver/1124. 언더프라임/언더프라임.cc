#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int a, b;
bool is_prime[100'001];
vector<int> primes;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> a >> b;
}

void CalcPrimes() {
  memset(is_prime, true, sizeof(is_prime));
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= 100'000; ++i)
    if (is_prime[i])
      for (int j = i + i; j <= 100'000; j += i)
        is_prime[j] = false;

  for (int i = 2; i <= 100'000; ++i)
    if (is_prime[i])
      primes.push_back(i);
}

int PrimeFactorization(int val) {
  int prime_count = 0;
  for (int prime : primes) {
    while (val % prime == 0) {
      ++prime_count;
      val /= prime;
    }

    if (val == 1)
      break;
  }

  return prime_count;
}

void Solve() {
  int answer = 0;
  CalcPrimes();
  for (int i = a; i <= b; ++i)
    if (is_prime[PrimeFactorization(i)])
      ++answer;

  cout << answer << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}