#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

int64_t a, b;
vector<bool> is_prime(10'000'001, true);

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> a >> b;
}

void Solve() {
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= 10'000'000; ++i)
    if (is_prime[i])
      for (int j = i * 2; j <= 10'000'000; j += i)
        is_prime[j] = false;
  
  int answer = 0;
  for (int64_t i = 1; i <= 10'000'000; ++i) {
    if (is_prime[i]) {
      __int128_t square = i * i;

      while (square < a) {
        square *= i;
      }

      while (square <= b) {
        ++answer;
        square *= i;
      }
    }
  }

  cout << answer << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}