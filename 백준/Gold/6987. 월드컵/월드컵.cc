#include <iostream>
#include <vector>
#include <utility>
using namespace std;

vector<vector<vector<int>>> scores(4, vector<vector<int>>(6, vector<int>(3)));
vector<pair<int, int>> matches;
vector<vector<int>> score(6, vector<int>(3));
vector<bool> is_valid(4);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 6; ++j)
      for (int k = 0; k < 3; ++k)
        cin >> scores[i][j][k];
}

void FindAllScores(int match_index) {
  if (match_index == ssize(matches)) {
    for (int i = 0; i < 4; ++i)
      if (scores[i] == score)
        is_valid[i] = true;
    return;
  }

  int team1 = matches[match_index].first;
  int team2 = matches[match_index].second;

  ++score[team1][0];
  ++score[team2][2];
  FindAllScores(match_index + 1);
  --score[team1][0];
  --score[team2][2];

  ++score[team1][1];
  ++score[team2][1];
  FindAllScores(match_index + 1);
  --score[team1][1];
  --score[team2][1];

  ++score[team1][2];
  ++score[team2][0];
  FindAllScores(match_index + 1);
  --score[team1][2];
  --score[team2][0];
}

void Solve() {
  for (int i = 0; i < 6; ++i)
    for (int j = i + 1; j < 6; ++j)
      matches.push_back({ i, j });

  FindAllScores(0);
  
  for (bool v : is_valid)
    cout << v << ' ';
  cout << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
