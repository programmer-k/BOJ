#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>
using namespace std;

int n;
vector<int64_t> nodes;
vector<int> parents;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  nodes.resize(n + 1);
  parents.resize(n + 1);
  for (int i = 2; i <= n; ++i) {
    char t;
    int a;
    cin >> t >> a >> parents[i];
    
    if (t == 'W')
      nodes[i] = -a;
    else
      nodes[i] = a;
  }
}

int64_t TopologicalSort() {
  vector<int> in_degrees(n + 1);
  for (int i = 2; i <= n; ++i)
    ++in_degrees[parents[i]];

  queue<int> q;
  for (int i = 1; i <= n; ++i)
    if (in_degrees[i] == 0)
      q.push(i);

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    if (nodes[node] > 0)
      nodes[parents[node]] += nodes[node];

    if (--in_degrees[parents[node]] == 0)
      q.push(parents[node]);
  }

  return nodes[1];
}

void Solve() {
  cout << TopologicalSort() << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
