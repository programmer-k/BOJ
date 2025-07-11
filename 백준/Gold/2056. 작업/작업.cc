#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n;
vector<int> costs(10'001);
vector<int> in_degrees(10'001);
vector<vector<int>> edges(10'001);
vector<int> answers(10'001);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> costs[i] >> in_degrees[i];

    for (int j = 1; j <= in_degrees[i]; ++j) {
      int from;
      cin >> from;
      edges[from].push_back(i);
    }
  }
}

int TopologicalSort() {
  queue<int> q;
  
  for (int i = 1; i <= n; ++i)
    if (in_degrees[i] == 0) {
      q.push(i);
      answers[i] = costs[i];
    }

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int next_node : edges[node]) {
      if (--in_degrees[next_node] == 0)
        q.push(next_node);
      answers[next_node] = max(answers[next_node], answers[node] + costs[next_node]);
    }
  }

  return *max_element(answers.begin(), answers.end());
}

void Solve() {
  cout << TopologicalSort() << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}