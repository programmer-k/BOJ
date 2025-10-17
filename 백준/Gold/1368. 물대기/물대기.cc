#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

class UnionFind {
 public:
  UnionFind(int size) : parents_(size) {
    for (int i = 0; i < size; ++i)
      parents_[i] = i;
  }

  int Find(int x) {
    if (x == parents_[x])
      return x;
    return parents_[x] = Find(parents_[x]);
  }

  bool Union(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y)
      return false;

    parents_[y] = x;
    return true;
  }

 private:
  vector<int> parents_;
};

struct Edge {
  int node1;
  int node2;
  int cost;

  bool operator<(const Edge& rhs) const {
    return tie(cost, node1, node2) < tie(rhs.cost, rhs.node1, rhs.node2);
  }
};

int n;
vector<int> weights;
vector<vector<int>> costs(300, vector<int>(300));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  weights.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> weights[i];

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> costs[i][j];
}

void GenerateEdges(vector<Edge>& edges) {
  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
      edges.push_back({i, j, costs[i][j]});
}

void Kruskal(vector<Edge>& edges, vector<vector<pair<int, int>>>& mst) {
  sort(edges.begin(), edges.end());

  UnionFind union_find(n);
  for (const Edge& edge : edges) {
    if (union_find.Union(edge.node1, edge.node2)) {
      mst[edge.node1].push_back({edge.node2, edge.cost});
      mst[edge.node2].push_back({edge.node1, edge.cost});
      //cout << edge.node1 << '-' << edge.node2 << ": " << edge.cost << '\n';
    }
  }
}

void DepthFirstSearch(int i, int& min_val, int& index1, int& index2,
                      int& index3, vector<bool>& visited,
                      const vector<bool>& selected_nodes,
                      const set<pair<int, int>>& selected_edges,
                      const vector<vector<pair<int, int>>>& mst) {
  visited[i] = true;
  for (const pair<int, int>& edge : mst[i]) {
    if (selected_edges.contains({min(i, edge.first), max(i, edge.first)})) {
      if (!selected_nodes[edge.first] && weights[edge.first] < min_val) {
        min_val = weights[edge.first];
        index1 = -1;
        index2 = -1;
        index3 = edge.first;
      }

      if (!visited[edge.first])
        DepthFirstSearch(edge.first, min_val, index1, index2, index3, visited,
                         selected_nodes, selected_edges, mst);
    } else {
      if (edge.second < min_val) {
        min_val = edge.second;
        index1 = min(i, edge.first);
        index2 = max(i, edge.first);
        index3 = -1;
      }
    }
  }
}

int CalculateMinCost(const vector<vector<pair<int, int>>>& mst) {
  int min_cost = 0;
  vector<bool> selected_nodes(n);
  set<pair<int, int>> selected_edges;
  for (int i = 0; i < n; ++i) {
    int min_val = weights[i];
    int index1 = -1;
    int index2 = -1;
    int index3 = -1;
    vector<bool> visited(n);
    DepthFirstSearch(i, min_val, index1, index2, index3, visited,
                     selected_nodes, selected_edges, mst);

    if (!(index1 == -1 && index2 == -1))
      selected_edges.insert({index1, index2});

    if (index3 != -1)
      selected_nodes[index3] = true;

    //cout << i << ": " << min_val << '\n';
    min_cost += min_val;
  }

  return min_cost;
}

void Solve() {
  vector<Edge> edges;
  vector<vector<pair<int, int>>> mst(n);
  GenerateEdges(edges);
  Kruskal(edges, mst);
  cout << CalculateMinCost(mst) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
