#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Data {
  string str;
  
  bool operator<(const Data& rhs) const {
    bool all_zero = true;
    for (int i = 0; i < ssize(str); ++i)
      

    if (str.size() != rhs.str.size())
      return str.size() < rhs.str.size();
    return str < rhs.str;
  }
};

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

void Solve1() {
  vector<string> dp(m + 1);

  for (int i = 0; i <= m; ++i)
    for (int j = 0; j < n; ++j)
      if (i - prices[j] >= 0)
        if (dp[i - prices[j]] != to_string(0))
          dp[i] = max(dp[i], dp[i - prices[j]] + to_string(j), Compare);

  string answer;
  for (int i = 0; i <= m; ++i)
    answer = max(answer, dp[i], Compare);
  //cout << dp[m] << '\n';
  cout << answer << '\n';
}

void Solve() {
  vector<vector<Data>> dp(m + 1, vector<Data>(n));
  for (int i = 0; i <= m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i - prices[j] >= 0) {
        if (dp[i - prices[j]][j].str == to_string(0)) {
          dp[i][j].str = to_string(0);
        } else {
          for (int k = 0; k < n; ++k)
            if (i - prices[k] >= 0)
            for (int l = 0; l < n; ++l)
              dp[i][j] = max(dp[i][j], Data(dp[i - prices[k]][l].str + to_string(k)));
        }
      }
    }
  }

  for (int i = 0; i <= m; ++i) {
    cout << i << ": ";
    for (int j = 0; j < n; ++j) {
      cout << dp[i][j].str << ' ';
    }
    cout << '\n';
  }

  Data answer;
  for (int i = 0; i < n; ++i)
    answer = max(answer, dp[m][i]);
  cout << answer.str << '\n';
}

int main() {
  GetInput();
  //Solve();
  Solve1();
  return 0;
}
