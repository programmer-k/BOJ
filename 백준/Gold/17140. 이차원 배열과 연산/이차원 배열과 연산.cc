#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int r, c, k;
vector<vector<int>> arr(3, vector<int>(3));

void GetInput() {
  cin >> r >> c >> k;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      cin >> arr[i][j];
}

bool SortPairs(const pair<int, int>& p1, const pair<int, int>& p2) {
  if (p1.second == p2.second)
    return p1.first < p2.first;
  return p1.second < p2.second;
}

void R() {
  vector<vector<int>> new_arr(ssize(arr));
  for (int i = 0; i < ssize(arr); ++i) {
    vector<int> counts(101);
    for (int j = 0; j < ssize(arr[i]); ++j) {
      ++counts[arr[i][j]];
    }

    vector<pair<int, int>> pairs;
    for (int j = 1; j <= 100; ++j) {
      if (counts[j] > 0) {
        pairs.push_back({ j, counts[j] });
      }
    }

    sort(pairs.begin(), pairs.end(), SortPairs);

    for (int j = 0; j < ssize(pairs); ++j) {
      new_arr[i].push_back(pairs[j].first);
      new_arr[i].push_back(pairs[j].second);
    }
  }

  int max_col = 0;
  for (int i = 0; i < ssize(new_arr); ++i) {
    max_col = max(max_col, static_cast<int>(ssize(new_arr[i])));
  }
  max_col = min(max_col, 100);

  for (int i = 0; i < ssize(new_arr); ++i) {
    new_arr[i].resize(max_col);
  }

  arr = new_arr;
}

void Transpose() {
  vector<vector<int>> new_arr(ssize(arr[0]), vector<int>(ssize(arr)));
  for (int i = 0; i < ssize(arr); ++i) {
    for (int j = 0; j < ssize(arr[i]); ++j) {
      new_arr[j][i] = arr[i][j];
    }
  }
  arr = new_arr;
}

void C() {
  Transpose();
  R();
  Transpose();
}

void Solve() {
  int t = 0;
  while (t <= 100 && !(r <= ssize(arr) && c <= ssize(arr[0]) && arr[r - 1][c - 1] == k)) {
    ssize(arr) >= ssize(arr[0]) ? R() : C();
    ++t;
  }

  if (t <= 100)
    cout << t << '\n';
  else
    cout << "-1\n";
}

int main() {
  GetInput();
  Solve();
  return 0;
}