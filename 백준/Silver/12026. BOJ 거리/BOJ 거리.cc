#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <limits>
using namespace std;

int n;
string input;
map<char, char> next_ch = { { 'B', 'O' }, { 'O', 'J' }, { 'J', 'B' } };

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  cin >> input;
}

void Solve() {
  vector<int> dist(n, numeric_limits<int>::max());
  dist[0] = 0;
  for (int i = 0; i < n; ++i) {
    char current = input[i];
    char next = next_ch[current];

    if (dist[i] == numeric_limits<int>::max())
      continue;
    
    for (int j = i + 1; j < n; ++j) {
      if (input[j] == next) {
        int square = (j - i) * (j - i);
        dist[j] = min(dist[j], dist[i] + square);
      }
    }
  }

  if (dist[n - 1] == numeric_limits<int>::max())
    cout << "-1\n";
  else
    cout << dist[n - 1] << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}