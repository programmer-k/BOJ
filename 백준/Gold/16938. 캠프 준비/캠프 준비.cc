#include <iostream>
#include <array>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int n, l, r, x, answer;
array<int, 15> arr;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> l >> r >> x;
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

bool IsValid(vector<int>& selected) {
  int len = selected.size();

  if (len < 2)
    return false;

  int total = accumulate(selected.begin(), selected.end(), 0);
  
  if (total < l || total > r)
    return false;

  int max_val = *max_element(selected.begin(), selected.end());
  int min_val = *min_element(selected.begin(), selected.end());

  if (max_val - min_val < x)
    return false;
  return true;
}

void Select(int index, vector<int>& selected) {
  if (index == n) {
    if (IsValid(selected))
      ++answer;
    return;
  }

  selected.push_back(arr[index]);
  Select(index + 1, selected);
  selected.pop_back();
  Select(index + 1, selected);
}

void Solve() {
  vector<int> selected;
  Select(0, selected);
  cout << answer << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}