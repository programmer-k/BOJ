#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, k;
vector<int> r(100), c(100);
vector<vector<vector<int>>> stickers(100, vector<vector<int>>(10, vector<int>(10)));
vector<vector<int>> map(40, vector<int>(40));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> k;

  for (int i = 0; i < k; ++i) {
    cin >> r[i] >> c[i];
    
    for (int row = 0; row < r[i]; ++row)
      for (int col = 0; col < c[i]; ++col)
        cin >> stickers[i][row][col];
  }
}

void Rotate(int sticker_index) {
  vector<vector<int>>& sticker = stickers[sticker_index];
  vector<vector<int>> rotated_sticker(10, vector<int>(10));

  for (int i = 0; i < r[sticker_index]; ++i) {
    for (int j = 0; j < c[sticker_index]; ++j) {
      rotated_sticker[j][r[sticker_index] - i - 1] = sticker[i][j];
    }
  }

  swap(r[sticker_index], c[sticker_index]);
  for (int i = 0; i < r[sticker_index]; ++i) {
    for (int j = 0; j < c[sticker_index]; ++j) {
      sticker[i][j] = rotated_sticker[i][j];
    }
  }
}

bool Paint(int row, int col, int sticker_index) {
  int sticker_rows = r[sticker_index];
  int sticker_cols = c[sticker_index];
  vector<vector<int>>& sticker = stickers[sticker_index];
  
  for (int i = 0; i < sticker_rows; ++i) {
    for (int j = 0; j < sticker_cols; ++j) {
      int map_row = i + row;
      int map_col = j + col;

      if (sticker[i][j] == 1 && map[map_row][map_col] == 1) {
        return false;
      }
    }
  }

  //cout << "Paint at " << row << ", " << col << "\n";
  for (int i = 0; i < sticker_rows; ++i) {
    for (int j = 0; j < sticker_cols; ++j) {
      int map_row = i + row;
      int map_col = j + col;

      if (sticker[i][j] == 1) {
        map[map_row][map_col] = 1;
      }
    }
  }

  return true;
}

void Paint(int sticker_index) {
  for (int rotate = 0; rotate < 4; ++rotate) {
    for (int i = 0; i <= n - r[sticker_index]; ++i) {
      for (int j = 0; j <= m - c[sticker_index]; ++j) {
        if (Paint(i, j, sticker_index)) {
          return;
        }
      }
    }

    Rotate(sticker_index);
    //cout << "Rotate!" << '\n';
  }
}

void Solve() {
  for (int i = 0; i < k; ++i) {
    //cout << "Paint: " << i << '\n';
    Paint(i);

    /*for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << map[i][j] << ' ';
      }
      cout << '\n';
    }
    cout << "=========================\n";*/
  }

  int count = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (map[i][j] == 1) {
        ++count;
      }
    }
  }

  cout << count << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}