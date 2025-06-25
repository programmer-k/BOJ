#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
using namespace std;

int n;
array<int, 2'000> a, b;
vector<vector<int>> dp(2'000, vector<int>(2'000, -1));

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  
  for (int i = 0; i < n; ++i)
    cin >> b[i];
}

int CalculateMaxScore(int i, int j) {
  if (i == n || j == n)
    return 0;
  
  if (dp[i][j] != -1)
    return dp[i][j];
  
  int candidate1 = CalculateMaxScore(i + 1, j);
  int candidate2 = CalculateMaxScore(i + 1, j + 1);
  int candidate3 = 0;

  if (a[i] > b[j])
    candidate3 = CalculateMaxScore(i, j + 1) + b[j];

  return dp[i][j] = max({ candidate1, candidate2, candidate3 });
}

void Solve() {
  cout << CalculateMaxScore(0, 0) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}