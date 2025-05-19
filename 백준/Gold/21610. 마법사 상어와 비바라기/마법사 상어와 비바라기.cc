#include <iostream>
#include <array>
#include <vector>
using namespace std;

int n, m;
array<array<int, 51>, 51> water_map;
vector<vector<bool>> cloud_map(51, vector<bool>(51, false));
array<int, 100> d, s;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      cin >> water_map[i][j];

  for (int i = 0; i < m; ++i)
    cin >> d[i] >> s[i];
}

void MoveCloudAndRain(int direction, int step) {
  vector<vector<bool>> cloud_map_copy(51, vector<bool>(51, false));
  array<int, 9> move_rows = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
  array<int, 9> move_cols = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (!cloud_map[i][j])
        continue;
      
      int next_row = i + move_rows[direction] * step;
      int next_col = j + move_cols[direction] * step;
      next_row = ((next_row - 1 + 50 * n) % n) + 1;
      next_col = ((next_col - 1 + 50 * n) % n) + 1;

      cloud_map_copy[next_row][next_col] = true;
      ++water_map[next_row][next_col];
    }
  }

  cloud_map = cloud_map_copy;
}

void WaterCopyBug() {
  array<int, 4> move_rows = { -1, -1, 1, 1 };
  array<int, 4> move_cols = { -1, 1, 1, -1 };

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (!cloud_map[i][j])
        continue;
      
      int water_count = 0;
      for (int k = 0; k < 4; ++k) {
        int next_row = i + move_rows[k];
        int next_col = j + move_cols[k];

        if (next_row <= 0 || next_col <= 0 || next_row > n || next_col > n)
          continue;
        
        if (water_map[next_row][next_col] > 0)
          ++water_count;
      }

      water_map[i][j] += water_count;
    }
  }
}

void CreateCloud() {
  vector<vector<bool>> cloud_map_copy(51, vector<bool>(51, false));

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (water_map[i][j] >= 2 && !cloud_map[i][j]) {
        cloud_map_copy[i][j] = true;
        water_map[i][j] -= 2;
      }
    }
  }

  cloud_map = cloud_map_copy;
}

int GetTotalWater() {
  int total = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      total += water_map[i][j];
  return total;
}

void Solve() {
  cloud_map[n][1] = true;
  cloud_map[n][2] = true;
  cloud_map[n - 1][1] = true;
  cloud_map[n - 1][2] = true;

  for (int i = 0; i < m; ++i) {
    MoveCloudAndRain(d[i], s[i]);
    WaterCopyBug();
    CreateCloud();
  }

  cout << GetTotalWater() << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}