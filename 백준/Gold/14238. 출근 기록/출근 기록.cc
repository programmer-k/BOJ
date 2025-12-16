#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

string s;
map<tuple<int, int, int, int, int>, string> dp;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> s;
}

string GenerateValidRecord(int a, int b, int c, int prev1, int prev2) {
  if (a == 0 && b == 0 && c == 0)
    return "";

  tuple<int, int, int, int, int> key = make_tuple(a, b, c, prev1, prev2);
  if (dp.contains(key))
    return dp[key];

  if (a > 0) {
    string result = GenerateValidRecord(a - 1, b, c, 0, prev1);
    if (result != "-1")
      return dp[key] = "A" + result;
  }

  if (b > 0 && prev1 != 1) {
    string result = GenerateValidRecord(a, b - 1, c, 1, prev1);
    if (result != "-1")
      return dp[key] = "B" + result;
  }

  if (c > 0 && prev1 != 2 && prev2 != 2) {
    string result = GenerateValidRecord(a, b, c - 1, 2, prev1);
    if (result != "-1")
      return dp[key] = "C" + result;
  }

  return dp[key] = "-1";
}

void Solve() {
  vector<int> counts(3);
  for (char ch : s)
    ++counts[ch - 'A'];

  string str;
  string result = GenerateValidRecord(counts[0], counts[1], counts[2], -1, -1);
  cout << (result.empty() ? "-1" : result) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
