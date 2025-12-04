#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int kIntMax = numeric_limits<int>::max();

int n, m;
vector<int> male, female;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  male.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> male[i];

  female.resize(m);
  for (int i = 0; i < m; ++i)
    cin >> female[i];
}

int Calculate(int male_index, int female_index, vector<vector<int>>& dp) {
  if (male_index >= ssize(male))
    return 0;
  
  if (dp[male_index][female_index] != -1)
    return dp[male_index][female_index];
  
  int min_val = kIntMax;
  for (int i = female_index; i < ssize(female); ++i) {
    int male_left = ssize(male) - male_index;
    int female_left = ssize(female) - i;
    
    if (male_left > female_left)
      break;

    int diff = abs(male[male_index] - female[i]);
    min_val = min(min_val, Calculate(male_index + 1, i + 1, dp) + diff);
  }

  return dp[male_index][female_index] = min_val;
}

void Solve() {
  sort(male.begin(), male.end());
  sort(female.begin(), female.end());

  if (ssize(male) > ssize(female))
    male.swap(female);

  vector<vector<int>> dp(ssize(male), vector<int>(ssize(female), -1));
  cout << Calculate(0, 0, dp) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
