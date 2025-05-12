#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n;
vector<string> inputs;
vector<int> strikes, balls;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    string input;
    int strike, ball;
    cin >> input >> strike >> ball;
    
    inputs.push_back(input);
    strikes.push_back(strike);
    balls.push_back(ball);
  }
}

int CountStrike(const string& guess, const string& actual) {
  int strike = 0;
  for (int i = 0; i < 3; ++i)
    if (guess[i] == actual[i])
      ++strike;
  return strike;
}

int CountBall(const string& guess, const string& actual) {
  int ball = 0;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i == j)
        continue;
      
      if (guess[i] == actual[j])
        ++ball;
    }
  }
  return ball;
}

void Solve() {
  int answer = 0;
  for (int i = 1; i <= 9; ++i) {
    for (int j = 1; j <= 9; ++j) {
      // duplicate
      if (i == j)
        continue;
      for (int k = 1; k <= 9; ++k) {
        // duplicate
        if (i == k || j == k)
          continue;

        bool is_correct = true;
        string actual = to_string(i) + to_string(j) + to_string(k);
        for (int l = 0; l < n; ++l) {
          int strike = CountStrike(inputs[l], actual);
          int ball = CountBall(inputs[l], actual);

          if (strike != strikes[l] || ball != balls[l]) {
            is_correct = false;
            break;
          }
        }

        if (is_correct)
          ++answer;
      }
    }
  }

  cout << answer << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}