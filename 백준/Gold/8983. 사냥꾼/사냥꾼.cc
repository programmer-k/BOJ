#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int m, n, l;
vector<int> shots;
vector<pair<int, int>> animals;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> m >> n >> l;

  shots.resize(m);
  for (int i = 0; i < m; ++i)
    cin >> shots[i];

  animals.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> animals[i].first >> animals[i].second;
}

void Solve() {
  sort(shots.begin(), shots.end());

  int count = 0;
  for (const pair<int, int>& animal : animals) {
    int index = lower_bound(shots.begin(), shots.end(), animal.first) - shots.begin();
    int dist = min(index > 0 ? animal.first - shots[index - 1] : 1'234'567'890, index < m ? shots[index] - animal.first : 1'234'567'890) + animal.second;

    if (dist <= l)
      ++count;
  }

  cout << count << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
