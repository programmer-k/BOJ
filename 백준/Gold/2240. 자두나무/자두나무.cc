#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int t, w;
vector<int> arr(1'000);
int dp[1'000][31][3];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> t >> w;

  for (int i = 0; i < t; ++i)
    cin >> arr[i];
}

int GetNextPos(int curr_pos) {
  if (curr_pos == 1)
    return 2;
  return 1;
}

int DepthFirstSearch(int index, int curr_w, int curr_pos) {
  if (curr_w > w)
    return -1'000'000;

  if (index == t) {
    return 0;
  }

  if (dp[index][curr_w][curr_pos] != -1)
    return dp[index][curr_w][curr_pos];

  int val1 = (curr_pos == arr[index] ? 1 : 0) + DepthFirstSearch(index + 1, curr_w, curr_pos);
  int val2 = (GetNextPos(curr_pos) == arr[index] ? 1 : 0) + DepthFirstSearch(index + 1, curr_w + 1, GetNextPos(curr_pos));

  return dp[index][curr_w][curr_pos] = max(val1, val2);
}

void Solve() {
  memset(dp, -1, sizeof(dp));
  cout << DepthFirstSearch(0, 0, 1) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}