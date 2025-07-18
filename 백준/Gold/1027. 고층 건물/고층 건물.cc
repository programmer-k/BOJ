#include <iostream>
#include <array>
using namespace std;

int n;
array<int, 51> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> arr[i];
}

bool CheckBuildingBlocksLine(int building, int line_from, int line_to) {
  int x = building;
  int x1 = line_from;
  int x2 = line_to;
  int y = arr[building];
  int y1 = arr[line_from];
  int y2 = arr[line_to];

  double threshold = static_cast<double>(y2 - y1) / (x2 - x1) * (x - x1) + y1;

  if (y >= threshold)
    return true;
  return false;
}

void Solve() {
  int max_count = 0;
  for (int i = 1; i <= n; ++i) {
    int count = 0;
    for (int j = 1; j <= n; ++j) {
      if (i == j)
        continue;
      
      bool is_blocked = false;
      for (int k = min(i, j) + 1; k < max(i, j); ++k)
        is_blocked |= CheckBuildingBlocksLine(k, min(i, j), max(i, j));

      if (!is_blocked)
        ++count;
    }
    
    max_count = max(max_count, count);
  }

  cout << max_count << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}