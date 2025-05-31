#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;
vector<int> arr(300'000);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

void Solve() {
  vector<int> diffs;
  
  for (int i = 0; i < n - 1; ++i)
    diffs.push_back(arr[i + 1] - arr[i]);
  
  sort(diffs.begin(), diffs.end());

  int answer = 0;
  for (int i = 0; i < ssize(diffs) - (k - 1); ++i)
    answer += diffs[i];
  cout << answer << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}