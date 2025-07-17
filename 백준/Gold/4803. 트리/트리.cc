#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<vector<int>> edges(501);
vector<int> visited(501);

void GetInput1() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
}

bool GetInput2() {
  cin >> n >> m;

  if (n == 0 && m == 0)
    return false;
  
  fill(visited.begin(), visited.end(), false);
  for (int i = 1; i <= 500; ++i)
    edges[i].clear();

  for (int i = 0; i < m; ++i) {
    int node1, node2;
    cin >> node1 >> node2;
    edges[node1].push_back(node2);
    edges[node2].push_back(node1);
  }
  
  return true;
}

bool DepthFirstSearch(int node) {
  bool is_graph = false;
  int visited_count = 0;
  visited[node] = true;
  
  for (int next_node : edges[node]) {
    if (visited[next_node])
      ++visited_count;
    else if (!DepthFirstSearch(next_node))
      is_graph = true;
  }

  if (!is_graph && visited_count <= 1)
    return true;
  return false;
}

void Solve() {
  static int test_case = 0;
  int answer = 0;

  for (int i = 1; i <= n; ++i)
    if (!visited[i] && DepthFirstSearch(i))
      ++answer;

  cout << "Case " << ++test_case << ": ";
  if (answer == 0)
    cout << "No trees.\n";
  else if (answer == 1)
    cout << "There is one tree.\n";
  else
    cout << "A forest of " << answer << " trees.\n";
}

int main() {
  GetInput1();
  while (GetInput2())
    Solve();
  return 0;
}