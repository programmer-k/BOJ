#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

int n, m;
array<int, 50> cranes, positions;
array<int, 10'000> boxes;
array<bool, 10'000> moves;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> cranes[i];
  
  cin >> m;
  for (int i = 0; i < m; ++i)
    cin >> boxes[i];
}

void Solve() {
  sort(cranes.begin(), cranes.begin() + n, greater<int>());
  sort(boxes.begin(), boxes.begin() + m, greater<int>());

  if (cranes[0] < boxes[0]) {
    cout << "-1\n";
    return;
  }

  int tick = 0;
  int move_count = 0;
  while (move_count < m) {
    for (int i = 0; i < n; ++i) {
      for (int& j = positions[i]; j < m; ++j) {
        if (!moves[j] && cranes[i] >= boxes[j]) {
          moves[j] = true;
          ++move_count;
          ++j;
          break;
        }
      }
    }
    ++tick;
  }

  cout << tick << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}