#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> parents;
vector<vector<int>> edges;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  parents.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> parents[i];
}

int DepthFirstSearch(int node) {
  if (ssize(edges[node]) == 0)
    return 1;

  vector<int> arr;
  for (int next_node : edges[node])
    arr.push_back(DepthFirstSearch(next_node));

  sort(arr.begin(), arr.end());
  for (int i = 0; i < ssize(arr); ++i)
    arr[i] += ssize(arr) - i;

  return *max_element(arr.begin(), arr.end());
}

void Solve() {
  edges.resize(n);
  for (int i = 1; i < n; ++i)
    edges[parents[i]].push_back(i);

  cout << DepthFirstSearch(0) - 1 << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
