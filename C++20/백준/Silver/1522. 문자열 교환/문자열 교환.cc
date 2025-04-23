#include <iostream>
#include <string>
using namespace std;

string input;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> input;
}

void Solve() {
  int a_count = 0;
  for (int i = 0; i < ssize(input); ++i)
    if (input[i] == 'a')
      ++a_count;

  int curr_a_count = 0;
  for (int i = 0; i < a_count; ++i)
    if (input[i] == 'a')
      ++curr_a_count;

  int left = 0;
  int right = a_count;
  int answer = a_count - curr_a_count;
  while (left < ssize(input) - 1) {
    if (input[right++ % ssize(input)] == 'a')
      ++curr_a_count;
    if (input[left++ % ssize(input)] == 'a')
      --curr_a_count;
    
    answer = min(answer, a_count - curr_a_count);
  }

  cout << answer << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}