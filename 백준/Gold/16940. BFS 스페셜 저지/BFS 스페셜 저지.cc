#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <set>
using namespace std;

int n;
vector<set<int>> edges;
vector<int> visit_order;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  edges.resize(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    int node1, node2;
    cin >> node1 >> node2;
    edges[node1].insert(node2);
    edges[node2].insert(node1);
  }

  visit_order.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> visit_order[i];
}

void Solve() {
  if (visit_order[0] != 1) {
    cout << "0\n";
    return;
  }

  int j = 1;
  for (int i = 0; i < n && j < n; ++i) {
    for (; j < n; ++j) {
      if (!edges[visit_order[i]].contains(visit_order[j])) {
        break;
      }
    }
  }

  if (j == n)
    cout << "1\n";
  else
    cout << "0\n";
}

int main() {
  GetInput();
  Solve();
  return 0;
}
