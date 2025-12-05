#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

struct Rule {
  int a, b, c;
};

int n, k, d;
vector<Rule> rules;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> k >> d;

  rules.resize(k);
  for (int i = 0; i < k; ++i)
    cin >> rules[i].a >> rules[i].b >> rules[i].c;
}

bool CanAccomodate(int box_num) {
  int64_t total = 0;
  for (int i = 0; i < k; ++i)
    if (rules[i].a <= box_num)
      total += (min(box_num, rules[i].b) - rules[i].a) / rules[i].c + 1;

  return total >= d;
}

void Solve() {
  int left = 1;
  int right = n;

  while (left < right) {
    int mid = (left + right) / 2;
    if (CanAccomodate(mid))
      right = mid;
    else
      left = mid + 1;
  }

  cout << left << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
