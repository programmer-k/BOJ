#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <algorithm>
using namespace std;

int n;
string inputs[30];
vector<string> splits[30];
pair<int, int> pos[30];
bool alphabets[26];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  cin.ignore();
  for (int i = 0; i < n; ++i)
    getline(cin, inputs[i]);
}

void Split(int i) {
  string str;
  stringstream ss(inputs[i]);
  while (getline(ss, str, ' '))
    splits[i].push_back(str);
}

int GetIndex(char alphabet) {
  return alphabet >= 'a' ? alphabet - 'a' : alphabet - 'A';
}

void Solve() {
  fill(pos, pos + 30, make_pair(-1, -1));
  for (int i = 0; i < n; ++i) {
    Split(i);

    bool found = false;
    for (int j = 0; j < ssize(splits[i]); ++j) {
      int k = GetIndex(splits[i][j][0]);
      if (!alphabets[k]) {
        alphabets[k] = true;
        found = true;
        pos[i].first = j;
        pos[i].second = 0;
        break;
      }
    }

    if (found)
      continue;
    
    for (int j = 0; j < ssize(splits[i]); ++j) {
      for (int l = 0; l < ssize(splits[i][j]); ++l) {
        int k = GetIndex(splits[i][j][l]);
        if (!alphabets[k]) {
          alphabets[k] = true;
          found = true;
          pos[i].first = j;
          pos[i].second = l;
          break;
        }
      }

      if (found)
        break;
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < ssize(splits[i]); ++j) {
      for (int k = 0; k < ssize(splits[i][j]); ++k) {
        if (j == pos[i].first && k == pos[i].second) {
          cout << '[' << splits[i][j][k] << ']';
        } else {
          cout << splits[i][j][k];
        }
      }
      cout << ' ';
    }
    cout << '\n';
  }
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}