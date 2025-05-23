#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> edges(51);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  while (true) {
    int member1, member2;
    cin >> member1 >> member2;

    if (member1 == -1 && member2 == -1)
      break;

    edges[member1].push_back(member2);
    edges[member2].push_back(member1);
  }
}

int BreadthFirstSearch(int member) {
  queue<int> q;
  vector<int> visited(n + 1, -1);
  q.push(member);
  visited[member] = 0;

  while (!q.empty()) {
    int curr_member = q.front();
    q.pop();

    for (int next_member : edges[curr_member]) {
      if (visited[next_member] == -1) {
        q.push(next_member);
        visited[next_member] = visited[curr_member] + 1;
      }
    }
  }

  return *max_element(visited.begin(), visited.end());
}

void Solve() {
  vector<int> scores(n + 1);
  for (int i = 1; i <= n; ++i) {
    scores[i] = BreadthFirstSearch(i);
  }

  int candidate_score = *min_element(scores.begin() + 1, scores.end());
  int candidate_num = count(scores.begin() + 1, scores.end(), candidate_score);
  cout << candidate_score << ' ' << candidate_num << '\n';

  for (int i = 1; i <= n; ++i) {
    if (scores[i] == candidate_score) {
      cout << i << ' ';
    }
  }
  cout << '\n';
}

int main(void) {
  GetInput();
  Solve();
  return 0;
}