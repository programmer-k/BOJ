#include <iostream>
#include <utility>
#include <array>
using namespace std;

int n;
array<pair<int, int>, 8> eggs;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> eggs[i].first >> eggs[i].second;
}

int GetMaxBrokenEggs(int index) {
  if (index >= n) {
    int broken_count = 0;
    for (int i = 0; i < n; ++i)
      if (eggs[i].first <= 0)
        ++broken_count;
    return broken_count;
  }
  
  if (eggs[index].first <= 0)
    return GetMaxBrokenEggs(index + 1);

  bool is_hit = false;
  int max_val = 0;
  for (int i = 0; i < n; ++i) {
    if (i == index)
      continue;
    
    if (eggs[i].first <= 0)
      continue;
    
    is_hit = true;
    eggs[index].first -= eggs[i].second;
    eggs[i].first -= eggs[index].second;
    max_val = max(max_val, GetMaxBrokenEggs(index + 1));
    eggs[index].first += eggs[i].second;
    eggs[i].first += eggs[index].second;
  }

  if (!is_hit)
    return n - 1;

  return max_val;
}

void Solve() {
  cout << GetMaxBrokenEggs(0) << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}