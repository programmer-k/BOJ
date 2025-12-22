#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

int64_t min_val, max_val;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> min_val >> max_val;
}

void Solve() {
  vector<bool> is_square_no_no_nums(max_val - min_val + 1, true);
  for (int64_t i = 2; i <= 1'000'000; ++i) {
    int64_t square = i * i;
    int64_t start =
        min_val % square == 0 ? min_val / square : min_val / square + 1;

    for (int64_t j = square * start; j - min_val < ssize(is_square_no_no_nums);
         j += square)
      is_square_no_no_nums[j - min_val] = false;
  }

  cout << count(is_square_no_no_nums.begin(), is_square_no_no_nums.end(), true)
       << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
