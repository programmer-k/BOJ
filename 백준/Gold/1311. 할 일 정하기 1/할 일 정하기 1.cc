#include <cstring>
#include <iostream>
#include <limits>
using namespace std;

int n;
int costs[20][20];
int dp[20][1 << 20];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> costs[i][j];
}

int CalculateMinCost(int person, int visited) {
  if (person == n)
    return 0;

  if (dp[person][visited] != -1)
    return dp[person][visited];

  dp[person][visited] = numeric_limits<int>::max();
  for (int job = 0; job < n; ++job) {
    if (visited & (1 << job))
      continue;

    int next_visited = visited | (1 << job);
    dp[person][visited] =
        min(dp[person][visited],
            CalculateMinCost(person + 1, next_visited) + costs[person][job]);
  }

  return dp[person][visited];
}

void Solve() {
  memset(dp, -1, sizeof(dp));
  cout << CalculateMinCost(0, 0) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
