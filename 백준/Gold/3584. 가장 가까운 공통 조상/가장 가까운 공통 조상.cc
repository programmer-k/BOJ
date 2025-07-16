#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

int t;
int n;
int node1, node2;
array<int, 10'001> parents, depths;
vector<vector<int>> edges(10'001);

void GetInput1() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> t;
}

void GetInput2() {
  parents.fill(-1);
  depths.fill(-1);
  for (vector<int>& vec : edges)
    vec.clear();
  
  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    parents[b] = a;
    edges[a].push_back(b);
  }
  cin >> node1 >> node2;
}

void DepthFirstSearch(int node, int depth) {
  depths[node] = depth;
  for (int next_node : edges[node])
    if (depths[next_node] == -1)
      DepthFirstSearch(next_node, depth + 1);
}

int NearestCommonAncestor() {
  int depth1 = depths[node1];
  int depth2 = depths[node2];

  while (depth1 > depth2) {
    node1 = parents[node1];
    --depth1;
  }

  while (depth2 > depth1) {
    node2 = parents[node2];
    --depth2;
  }

  while (node1 != node2) {
    node1 = parents[node1];
    node2 = parents[node2];
  }

  return node1;
}

void Solve() {
  int root = find(parents.begin() + 1, parents.begin() + 1 + n, -1) - parents.begin();
  DepthFirstSearch(root, 1);
  cout << NearestCommonAncestor() << '\n';
}

int main() {
  GetInput1();
  for (int i = 0; i < t; ++i) {
    GetInput2();
    Solve();
  }
  return 0;
}