#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<int> answer;
int cnt;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> k;
}

void FindKth(int val) {
  if (val == 0) {
    if (++cnt == k) {
      cout << answer[0];
      for (int i = 1; i < ssize(answer); ++i)
        cout << '+' << answer[i];
      cout << '\n';
      exit(0);
    }
  }

  for (int i = 1; i <= min(val, 3); ++i) {
    answer.push_back(i);
    FindKth(val - i);
    answer.pop_back();
  }
}

void Solve() {
  FindKth(n);
  cout << "-1\n";
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}