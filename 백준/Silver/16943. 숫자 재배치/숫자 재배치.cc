#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

string a, b;
int answer = -1;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> a >> b;
}

void CalcMax(int index, vector<bool>& selected, string& result) {
  if (index == ssize(a)) {
    int val = atoi(result.c_str());
    if (val < atoi(b.c_str()))
      answer = max(answer, val);
    return;
  }

  for (int i = 0; i < ssize(a); ++i) {
    if (selected[i])
      continue;
    
    if (index == 0 && a[i] == '0')
      continue;
    
    selected[i] = true;
    result.push_back(a[i]);
    CalcMax(index + 1, selected, result);
    selected[i] = false;
    result.pop_back();
  }
}

void Solve() {
  /*if (a.size() > b.size()) {
    cout << "-1\n";
    return;
  } else if (a.size() < b.size()) {
    sort(a.begin(), a.end(), greater<char>());
    cout << a << '\n';
  }*/

  vector<bool> selected(a.size(), false);
  string result;
  CalcMax(0, selected, result);
  cout << answer << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}