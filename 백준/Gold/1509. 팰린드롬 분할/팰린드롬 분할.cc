#include <cstring>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

string str;
int is_palindrome[2'500][2'500];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> str;
}

int IsPalindrome(int from, int to) {
  if (from > to)
    return 1;

  if (from == to)
    return is_palindrome[from][to] = 1;

  if (str[from] == str[to])
    return is_palindrome[from][to] = IsPalindrome(from + 1, to - 1);
  else
    return is_palindrome[from][to] = 0;
}

void Solve() {
  memset(is_palindrome, -1, sizeof(is_palindrome));
  for (int i = 0; i < ssize(str); ++i)
    for (int j = i; j < ssize(str); ++j)
      if (is_palindrome[i][j] == -1)
        IsPalindrome(i, j);

  vector<int> dp(ssize(str), numeric_limits<int>::max());
  for (int i = 0; i < ssize(dp); ++i)
    for (int j = 0; j <= i; ++j)
      if (is_palindrome[j][i] == 1)
        dp[i] = min(dp[i], (j - 1 >= 0 ? dp[j - 1] : 0) + 1);

  cout << dp[ssize(str) - 1] << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
