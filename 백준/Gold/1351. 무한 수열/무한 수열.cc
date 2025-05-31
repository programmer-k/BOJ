#include <iostream>
#include <cstdint>
#include <unordered_map>
using namespace std;

int64_t n;
int p, q;
unordered_map<int64_t, int64_t> m;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n >> p >> q;
}

int64_t A(int64_t i) {
  if (i == 0)
    return 1;
  
  if (m.count(i))
    return m[i];
  
  return m[i] = A(i / p) + A(i / q);
}

void Solve() {
  cout << A(n) << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}