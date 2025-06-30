#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> forward_edges(501), backward_edges(501);

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    forward_edges[a].push_back(b);
    backward_edges[b].push_back(a);
  }
}

void VisitAll(queue<int>& q, vector<bool>& visited, vector<vector<int>>& edges) {
  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int next_node : edges[node]) {
      if (!visited[next_node]) {
        q.push(next_node);
        visited[next_node] = true;
      }
    }
  }
}

bool BreadthFirstSearch(int start) {
  queue<int> q;
  vector<bool> visited(n + 1, false);
  
  q.push(start);
  visited[start] = true;
  VisitAll(q, visited, forward_edges);

  q.push(start);
  VisitAll(q, visited, backward_edges);

  int count = 0;
  for (int i = 1; i <= n; ++i)
    if (visited[i])
      ++count;
  
  if (count == n)
    return true;
  return false;
}

void Solve() {
  int answer = 0;
  for (int i = 1; i <= n; ++i)
    if (BreadthFirstSearch(i))
      ++answer;
  cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}