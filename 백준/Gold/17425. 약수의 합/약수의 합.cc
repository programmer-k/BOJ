#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <cstdint>
using namespace std;

int t;
array<int, 100'000> arr;
vector<int> f(1'000'001, 1);
vector<int64_t> g(1'000'001);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  
  cin >> t;
  for (int i = 0; i < t; ++i)
    cin >> arr[i];
}

void CalculateG() {
  for (int i = 2; i <= 1'000'000; ++i)
    for (int j = i; j <= 1'000'000; j += i)
      f[j] += i;

  for (int i = 1; i <= 1'000'000; ++i)
    g[i] = g[i - 1] + f[i];
}

void Solve() {
  for (int i = 0; i < t; ++i)
    cout << g[arr[i]] << '\n';
}

int main() {
  CalculateG();
  GetInput();
  Solve();
  return 0;
}