#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int n;
vector<vector<char>> sign_matrix(10, vector<char>(10));
vector<int> answers;
int total;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = i; j < n; ++j)
      cin >> sign_matrix[i][j];
}

void FindPossibleSequence(int index) {
  if (index == n) {
    for (int answer : answers)
      cout << answer << ' ';
    cout << '\n';
    exit(0);
  }

  for (int i = -10; i <= 10; ++i) {
    bool is_valid = true;
    int to = index;

    answers.push_back(i);
    for (int from = index; from >= 0; --from) {
      int sum = 0;
      
      for (int j = from; j <= to; ++j)
        sum += answers[j];
      
      if (!((sum > 0 && sign_matrix[from][to] == '+') || (sum < 0 && sign_matrix[from][to] == '-') || (sum == 0 && sign_matrix[from][to] == '0'))) {
        is_valid = false;
        break;
      }
    }

    if (is_valid)
      FindPossibleSequence(index + 1);

    answers.pop_back();
  }
}

void Solve() {
  FindPossibleSequence(0);
}

int main() {
  GetInput();
  Solve();
  return 0;
}
