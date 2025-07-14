#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
using namespace std;

int n;
array<array<int, 10>, 51> scores;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  
  cin >> n;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= 9; ++j)
      cin >> scores[i][j];
}

int CalculateScore(vector<int>& positions) {
  int total_score = 0;
  int player_index = 0;
  for (int inning = 1; inning <= n; ++inning) {
    int out_count = 0;
    array<bool, 3> grounds = { false, false, false };
    while (out_count < 3) {
      int activity = scores[inning][positions[player_index]];

      if (activity == 1) {
        if (grounds[2])
          ++total_score;
        
        for (int i = 1; i >= 0; --i)
          grounds[i + 1] = grounds[i];
        grounds[0] = true;
      } else if (activity == 2) {
        for (int i = 1; i < 3; ++i)
          if (grounds[i])
            ++total_score;
        
        grounds[2] = grounds[0];
        grounds[1] = true;
        grounds[0] = false;
      } else if (activity == 3) {
        for (int i = 0; i < 3; ++i)
          if (grounds[i])
            ++total_score;
        
        for (int i = 0; i < 3; ++i)
          grounds[i] = false;
        grounds[2] = true;
      } else if (activity == 4) {
        int ground_count = 0;
        for (bool ground : grounds)
          if (ground)
            ++ground_count;
        
        total_score += ground_count + 1;

        for (bool& ground : grounds)
          ground = false;
      } else {
        ++out_count;
      }

      player_index = (player_index + 1) % 9;
    }
  }

  return total_score;
}

void Solve() {
  int max_score = 0;
  vector<int> positions = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  
  do {
    if (positions[3] == 1)
      max_score = max(max_score, CalculateScore(positions));
  } while (next_permutation(positions.begin(), positions.end()));

  cout << max_score << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}