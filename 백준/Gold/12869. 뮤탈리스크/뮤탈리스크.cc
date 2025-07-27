#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

int n;
vector<int> arr(3);
vector<int> attacks = { 9, 3, 1 };
vector<vector<vector<int>>> dp(61, vector<vector<int>>(61, vector<int>(61, -1)));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

int CalculateMinAttackCount(vector<int> scvs) {
  int idx1 = scvs[0] >= 0 ? scvs[0] : 0;
  int idx2 = scvs[1] >= 0 ? scvs[1] : 0;
  int idx3 = scvs[2] >= 0 ? scvs[2] : 0;

  if (idx1 == 0 && idx2 == 0 && idx3 == 0)
    return 0;

  if (dp[idx1][idx2][idx3] != -1)
    return dp[idx1][idx2][idx3];

  sort(scvs.begin(), scvs.end());

  int min_attack = numeric_limits<int>::max();
  do {
    vector<int> new_scvs(scvs);
    for (int i = 0; i < ssize(new_scvs); ++i)
      new_scvs[i] -= attacks[i];

    min_attack = min(min_attack, CalculateMinAttackCount(new_scvs) + 1);
  } while (next_permutation(scvs.begin(), scvs.end()));
  
  return dp[idx1][idx2][idx3] = min_attack;
}

void Solve() {
  cout << CalculateMinAttackCount(arr) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
