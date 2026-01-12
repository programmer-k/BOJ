#include <algorithm>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>
using namespace std;

struct Key {
  int node;
  int parent;
  bool is_parent_selected;

  bool operator<(const Key& rhs) const {
    return tie(node, parent, is_parent_selected) <
           tie(rhs.node, rhs.parent, rhs.is_parent_selected);
  }
};

int n;
int nodes[10'001];
vector<int> edges[10'001];
map<Key, int> dp;
map<Key, bool> trace;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  for (int i = 1; i <= n; ++i)
    cin >> nodes[i];

  for (int i = 0; i < n - 1; ++i) {
    int node1, node2;
    cin >> node1 >> node2;
    edges[node1].push_back(node2);
    edges[node2].push_back(node1);
  }
}

int CalcMaxIndependentSet(int node, int parent, bool is_parent_selected) {
  if (ssize(edges[node]) == 1 && edges[node][0] == parent) {
    if (is_parent_selected) {
      return 0;
    } else {
      trace[{node, parent, is_parent_selected}] = true;
      return nodes[node];
    }
  }

  if (dp.contains({node, parent, is_parent_selected}))
    return dp[{node, parent, is_parent_selected}];

  // If the parent is selected, then do not select current node always.
  if (is_parent_selected) {
    int total = 0;
    for (int next_node : edges[node]) {
      if (next_node == parent)
        continue;

      total += CalcMaxIndependentSet(next_node, node, false);
    }

    trace[{node, parent, is_parent_selected}] = false;
    return dp[{node, parent, is_parent_selected}] = total;
  }

  int total1 = 0;
  int total2 = nodes[node];
  for (int next_node : edges[node]) {
    if (next_node == parent)
      continue;

    int val1 = CalcMaxIndependentSet(next_node, node, false);
    int val2 = CalcMaxIndependentSet(next_node, node, true);

    total1 += val1;
    total2 += val2;
  }

  if (total1 >= total2) {
    trace[{node, parent, is_parent_selected}] = false;
    return dp[{node, parent, is_parent_selected}] = total1;
  } else {
    trace[{node, parent, is_parent_selected}] = true;
    return dp[{node, parent, is_parent_selected}] = total2;
  }
}

void FindPath(int node, int parent, bool is_parent_selected,
              vector<int>& result) {
  bool selected = trace[{node, parent, is_parent_selected}];

  if (selected) {
    result.push_back(node);
  }

  for (int next_node : edges[node]) {
    if (next_node == parent)
      continue;

    FindPath(next_node, node, selected, result);
  }
}

void Solve() {
  cout << CalcMaxIndependentSet(1, -1, false) << '\n';

  vector<int> result;
  FindPath(1, -1, false, result);
  sort(result.begin(), result.end());

  for (int val : result)
    cout << val << ' ';
  cout << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
