#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int n, m, r;
vector<vector<int>> arr(100, vector<int>(100));
vector<int> ops(1'000);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> r;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> arr[i][j];

  for (int i = 0; i < r; ++i)
    cin >> ops[i];
}

void VerticalFlip() {
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n / 2; ++i) {
      swap(arr[i][j], arr[n - 1 - i][j]);
    }
  }
}

void HorizontalFlip() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m / 2; ++j) {
      swap(arr[i][j], arr[i][m - 1 - j]);
    }
  }
}

void RightRotate() {
  vector<vector<int>> new_arr(100, vector<int>(100));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      new_arr[j][n - 1 - i] = arr[i][j];
    }
  }
  arr = new_arr;
}

void LeftRotate() {
  vector<vector<int>> new_arr(100, vector<int>(100));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      new_arr[m - 1 - j][i] = arr[i][j];
    }
  }
  arr = new_arr;
}

void MoveGroupForward() {
  int sub_row = n / 2;
  int sub_col = m / 2;
  vector<vector<int>> new_arr(100, vector<int>(100));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i < sub_row && j < sub_col)
        new_arr[i][j + sub_col] = arr[i][j];
      else if (i < sub_row && j >= sub_col)
        new_arr[i + sub_row][j] = arr[i][j];
      else if (i >= sub_row && j >= sub_col)
        new_arr[i][j - sub_col] = arr[i][j];
      else
        new_arr[i - sub_row][j] = arr[i][j];
    }
  }
  arr = new_arr;
}

void MoveGroupBackward() {
  int sub_row = n / 2;
  int sub_col = m / 2;
  vector<vector<int>> new_arr(100, vector<int>(100));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i < sub_row && j < sub_col)
        new_arr[i + sub_row][j] = arr[i][j];
      else if (i < sub_row && j >= sub_col)
        new_arr[i][j - sub_col] = arr[i][j];
      else if (i >= sub_row && j >= sub_col)
        new_arr[i - sub_row][j] = arr[i][j];
      else
        new_arr[i][j + sub_col] = arr[i][j];
    }
  }
  arr = new_arr;
}

void Apply(int op) {
  switch (op) {
  case 1:
    VerticalFlip();
    break;
  case 2:
    HorizontalFlip();
    break;
  case 3:
    RightRotate();
    swap(n, m);
    break;
  case 4:
    LeftRotate();
    swap(n, m);
    break;
  case 5:
    MoveGroupForward();
    break;
  case 6:
    MoveGroupBackward();
    break;
  default:
    break;
  }
}

void Solve() {
  for (int i = 0; i < r; ++i)
    Apply(ops[i]);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << arr[i][j] << ' ';
    }
    cout << '\n';
  }
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}