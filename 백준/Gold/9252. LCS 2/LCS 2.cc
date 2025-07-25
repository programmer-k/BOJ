#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string str1, str2;
int dp[1001][1001];

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> str1 >> str2;
}

void Visit(vector<char>& vec, int i, int j) {
  //cout << "Visit(" << i << ", " << j << ")" << endl;
  int vec_size = vec.size();
  if (vec_size == dp[str1.size() - 1][str2.size() - 1]) {
    reverse(vec.begin(), vec.end());
    for (size_t i = 0; i < vec.size(); ++i)
      cout << vec[i];
    cout << '\n';
    return;
  }

  if (str1[i] == str2[j]) {
    vec.push_back(str1[i]);
    Visit(vec, i - 1, j - 1);
  } else if (dp[i - 1][j] > dp[i][j - 1]) {
    Visit(vec, i - 1, j);
  } else {
    Visit(vec, i, j - 1);
  }
}

void Solve() {
  str1.insert(0, "1");
  str2.insert(0, "1");

  for (size_t i = 1; i < str1.size(); ++i)
    for (size_t j = 1; j < str2.size(); ++j)
      if (str1[i] == str2[j])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

  /*for (size_t i = 0; i < str1.size(); ++i) {
    for (size_t j = 0; j < str2.size(); ++j)
      cout << dp[i][j] << ' ';
    cout << '\n';
  }*/

  cout << dp[str1.size() - 1][str2.size() - 1] << '\n';
  vector<char> vec;
  Visit(vec, str1.size() - 1, str2.size() - 1);
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}