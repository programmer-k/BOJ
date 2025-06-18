#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

int t, k;
string w;

void GetInput1() {
  cin.tie(nullptr);
  cout.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> t;
}

void GetInput2() {
  cin >> w >> k;
}

int FindMinLength(char character) {
  int count = 0;
  int from = -1, to = 0;
  int answer1 = numeric_limits<int>::max();

  while (to < ssize(w)) {
    char ch = w[to];

    if (ch == character) {
      if (++count == k) {
        ++from;
        while (w[from] != character) {
          ++from;
        }
        answer1 = min(answer1, to - from + 1);
        --count;
      }
    }
    
    ++to;
  }

  return answer1;
}

int FindMaxLength(char character) {
  int count = 0;
  int from = -1, to = 0;
  int answer2 = 0;

  while (to < ssize(w)) {
    char ch = w[to];

    if (ch == character) {
      if (++count == k) {
        ++from;
        while (w[from] != character) {
          ++from;
        }
        answer2 = max(answer2, to - from + 1);
        --count;
      }
    }
    
    ++to;
  }

  return answer2;
}

void Solve() {
  int answer1 = numeric_limits<int>::max();
  int answer2 = 0;

  for (char ch = 'a'; ch <= 'z'; ++ch)
    answer1 = min(answer1, FindMinLength(ch));

  for (char ch = 'a'; ch <= 'z'; ++ch)
    answer2 = max(answer2, FindMaxLength(ch));

  if (answer1 == numeric_limits<int>::max())
    cout << "-1\n";
  else
    cout << answer1 << ' ' << answer2 << '\n';
}

int main(void) {
  GetInput1();
  for (int i = 0; i < t; ++i) {
    GetInput2();
    Solve();
  }
  return 0;
}