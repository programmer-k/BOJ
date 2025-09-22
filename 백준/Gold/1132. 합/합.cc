#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <utility>
using namespace std;

int n;
vector<string> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  arr.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

int64_t Power(int base, int exp) {
  int64_t result = 1;
  for (int i = 0; i < exp; ++i)
    result *= base;
  return result;
}

void Solve() {
  vector<int64_t> counts(10);
  for (const string& str : arr) {
    for (int i = 0; i < ssize(str); ++i) {
      int pos = ssize(str) - i - 1;
      int index = str[i] - 'A';
      counts[index] += Power(10, pos);
    }
  }

  unordered_set<char> start_nums;
  for (const string& str : arr)
    start_nums.insert(str.front());

  vector<pair<int64_t, char>> highest_digit_counts;
  for (int i = 0; i < 10; ++i)
    highest_digit_counts.push_back({counts[i], i + 'A'});
  sort(highest_digit_counts.begin(), highest_digit_counts.end());

  char zero_alphabet = 0;
  for (const pair<int64_t, char>& p : highest_digit_counts) {
    if (!start_nums.contains(p.second)) {
      zero_alphabet = p.second;
      break;
    }
  }

  int val = 1;
  int64_t answer = 0;
  for (const pair<int64_t, char>& p : highest_digit_counts) {
    if (p.second != zero_alphabet) {
      answer += p.first * val++;
    }
  }

  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
