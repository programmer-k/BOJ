#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n, m;
vector<int> prices;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  prices.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> prices[i];

  cin >> m;
}

bool Compare(const string& str1, const string& str2) {
  if (str1.size() != str2.size())
    return str1.size() < str2.size();
  return str1 < str2;
}

void Solve() {
  vector<string> dp(m + 1);

  for (int i = 0; i <= m; ++i)
    for (int j = 0; j < n; ++j)
      if (i - prices[j] >= 0)
        if (dp[i - prices[j]] != to_string(0))
          dp[i] = max(dp[i], dp[i - prices[j]] + to_string(j), Compare);

  string answer;
  for (int i = 0; i <= m; ++i)
    answer = max(answer, dp[i], Compare);
  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
