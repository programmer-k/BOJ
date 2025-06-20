#include <iostream>
#include <array>
#include <set>
#include <string>
using namespace std;

int n, m;
array<array<char, 9>, 9> map;
set<int> candidates, squares;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> map[i][j];
}

bool InRange(int row, int col) {
  if (row >= 0 && row < n && col >= 0 && col < m)
    return true;
  return false;
}

void FindNumbersWithStep(int row, int col, int row_step, int col_step) {
  int curr_row = row;
  int curr_col = col;
  string str;
  
  while (InRange(curr_row, curr_col)) {
    str.push_back(map[curr_row][curr_col]);
    candidates.insert(stoi(str));
    
    curr_row += row_step;
    curr_col += col_step;
  }
}

void FindNumbers(int row, int col) {
  for (int row_step = -n; row_step < n; ++row_step) {
    for (int col_step = -m; col_step < m; ++col_step) {
      if (!(row_step == 0 && col_step == 0)) {
        FindNumbersWithStep(row, col, row_step, col_step);
      }
    }
  }
}

void FindAllSquareNumbers() {
  int num = 0;
  while (num * num < 1'000'000'000) {
    squares.insert(num * num);
    ++num;
  }
}

void Solve() {
  FindAllSquareNumbers();
  
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      FindNumbers(i, j);

  int answer = -1;
  for (int num : candidates) {
    if (squares.contains(num)) {
      answer = max(answer, num);
    }
  }

  cout << answer << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}