#include <iostream>
#include <map>
#include <set>
#include <utility>
using namespace std;

int n, m;
set<pair<int, int>> s;
map<int, int> dict;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 1; i <= n; ++i) {
    int num;
    cin >> num;
    s.insert({num, i});
    dict[i] = num;
  }

  cin >> m;
}

void Solve() {
  for (int i = 0; i < m; ++i) {
    int query;
    cin >> query;

    if (query == 1) {
      int index, new_value;
      cin >> index >> new_value;

      int value = dict[index];
      s.erase(s.find({value, index}));
      s.insert({new_value, index});

      dict[index] = new_value;
    } else {
      cout << (*s.begin()).second << '\n';
    }
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
