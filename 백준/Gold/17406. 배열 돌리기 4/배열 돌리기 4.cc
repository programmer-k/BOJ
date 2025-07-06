#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

struct Operation {
  int r;
  int c;
  int s;

  bool operator<(const Operation& rhs) const {
    if (this->r != rhs.r)
      return this->r < rhs.r;
    if (this->c != rhs.c)
      return this->c < rhs.c;
    return this->s < rhs.s;
  }
};

int n, m, k;
vector<vector<int>> arr_input(50, vector<int>(50));
vector<Operation> ops;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> k;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> arr_input[i][j];

  for (int i = 0; i < k; ++i) {
    int r, c, s;
    cin >> r >> c >> s;
    ops.push_back({ r - 1, c - 1, s });
  }
}

void Rotate(vector<vector<int>>& arr, int row, int col, int size) {
  for (int current_size = 1; current_size <= size; ++current_size) {
    int current_row = row - current_size;
    int current_col = col - current_size;
    int top_left_val = arr[current_row][current_col];

    while (current_row < row + current_size) {
      arr[current_row][current_col] = arr[current_row + 1][current_col];
      ++current_row;
    }

    while (current_col < col + current_size) {
      arr[current_row][current_col] = arr[current_row][current_col + 1];
      ++current_col;
    }

    while (current_row > row - current_size) {
      arr[current_row][current_col] = arr[current_row - 1][current_col];
      --current_row;
    }

    while (current_col > col - current_size + 1) {
      arr[current_row][current_col] = arr[current_row][current_col - 1];
      --current_col;
    }

    arr[current_row][current_col] = top_left_val;
  }
}

int GetMinRowSum(const vector<vector<int>>& arr) {
  int min_total = numeric_limits<int>::max();
  for (int i = 0; i < n; ++i) {
    int total = 0;
    for (int j = 0; j < m; ++j)
      total += arr[i][j];
    min_total = min(min_total, total);
  }
  return min_total;
}

void Solve() {
  int answer = numeric_limits<int>::max();
  sort(ops.begin(), ops.end());
  do {
    vector<vector<int>> arr_copy = arr_input;
    for (const Operation& op : ops)
      Rotate(arr_copy, op.r, op.c, op.s);

    answer = min(answer, GetMinRowSum(arr_copy));
  } while (next_permutation(ops.begin(), ops.end()));

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}