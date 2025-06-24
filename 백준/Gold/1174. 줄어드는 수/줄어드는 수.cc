#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int64_t> answers;

void GetInput() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
}

void FindDecreasingNum(string num) {
  answers.push_back(stoll(num));

  for (char ch = '0'; ch < num.back(); ++ch) {
    FindDecreasingNum(num + ch);
  }
}

void Solve() {
  for (int i = 0; i <= 9; ++i)
    FindDecreasingNum(to_string(i));

  sort(answers.begin(), answers.end());

  if (n > ssize(answers))
    cout << "-1\n";
  else
    cout << answers[n - 1] << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}