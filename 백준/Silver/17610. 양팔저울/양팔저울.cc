#include <iostream>
#include <array>
#include <numeric>
using namespace std;

int k;
array<int, 13> arr;
array<bool, 200'000 * 13 + 1> is_measureable;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> k;
  for (int i = 0; i < k; ++i)
    cin >> arr[i];
}

void FindMeasureableWater(int index, int sum) {
  if (index == k) {
    if (sum <= 0)
      return;
    
    is_measureable[sum] = true;
    return;
  }

  FindMeasureableWater(index + 1, sum);
  FindMeasureableWater(index + 1, sum + arr[index]);
  FindMeasureableWater(index + 1, sum - arr[index]);
}

void Solve() {
  is_measureable.fill(false);
  int total = accumulate(arr.begin(), arr.begin() + k, 0);
  FindMeasureableWater(0, 0);
  

  int count = 0;
  
  for (int i = 1; i <= total; ++i)
    if (!is_measureable[i])
      ++count;

  cout << count << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}