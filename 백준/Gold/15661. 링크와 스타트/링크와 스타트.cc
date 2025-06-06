#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int n;
vector<vector<int>> s(20, vector<int>(20));
int min_diff = numeric_limits<int>::max();

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> s[i][j];
}

int CalculateTeamPower(const vector<int>& team) {
  int team_power = 0;
  for (int member1 : team)
    for (int member2: team)
      team_power += s[member1][member2];
  return team_power;
}

void SelectTeam(int index, vector<int>& team1, vector<int>& team2) {
  if (index == n) {
    if (team1.size() == 0 || team2.size() == 0)
      return;
    
    int team1_power = CalculateTeamPower(team1);
    int team2_power = CalculateTeamPower(team2);
    min_diff = min(min_diff, abs(team1_power - team2_power));
    return;
  }

  team1.push_back(index);
  SelectTeam(index + 1, team1, team2);
  team1.pop_back();
  
  team2.push_back(index);
  SelectTeam(index + 1, team1, team2);
  team2.pop_back();
}

void Solve() {
  vector<int> team1, team2;
  SelectTeam(0, team1, team2);
  cout << min_diff << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}