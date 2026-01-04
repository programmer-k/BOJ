#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

int n, m;
int ranks[501];
pair<int, int> changed_teams[25'000];
bool edges[501][501];
int in_degrees[501];

void GetInput() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> ranks[i];

  cin >> m;
  for (int i = 0; i < m; ++i)
    cin >> changed_teams[i].first >> changed_teams[i].second;
}

void InitEdges() {
  memset(edges, false, sizeof(edges));
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j)
      edges[ranks[i]][ranks[j]] = true;
}

vector<int> TopologicalSort() {
  for (int i = 0; i < m; ++i) {
    int team1 = changed_teams[i].first;
    int team2 = changed_teams[i].second;

    if (edges[team1][team2]) {
      edges[team1][team2] = false;
      edges[team2][team1] = true;
    } else {
      edges[team2][team1] = false;
      edges[team1][team2] = true;
    }
  }

  memset(in_degrees, 0, sizeof(in_degrees));
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (edges[i][j])
        ++in_degrees[j];

  queue<int> q;
  for (int i = 1; i <= n; ++i)
    if (in_degrees[i] == 0)
      q.push(i);

  vector<int> answers;
  while (!q.empty()) {
    int node = q.front();
    answers.push_back(node);
    q.pop();

    for (int next_node = 1; next_node <= n; ++next_node)
      if (edges[node][next_node] && --in_degrees[next_node] == 0)
        q.push(next_node);
  }

  return answers;
}

void Solve() {
  InitEdges();
  vector<int> answers = TopologicalSort();

  if (ssize(answers) != n) {
    cout << "IMPOSSIBLE\n";
    return;
  }

  for (int answer : answers)
    cout << answer << ' ';
  cout << '\n';
}

int main() {
  int test_case;
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> test_case;

  for (int i = 0; i < test_case; ++i) {
    GetInput();
    Solve();
  }

  return 0;
}
