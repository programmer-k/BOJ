#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

  void Union(int x, int y) {
    parents_[y] = x;
  }

 private:
  vector<int> parents_;
};

int n, m;
vector<string> names;
vector<pair<string, string>> ancestors;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  names.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> names[i];

  cin >> m;

  ancestors.resize(m);
  for (int i = 0; i < m; ++i)
    cin >> ancestors[i].first >> ancestors[i].second;
}

void TopologicalSort(const vector<vector<int>>& edges, vector<int>& levels) {
  vector<int> in_degrees(n);
  for (int i = 0; i < n; ++i)
    for (int next_node : edges[i])
      ++in_degrees[next_node];

  queue<int> q;
  for (int i = 0; i < n; ++i)
    if (in_degrees[i] == 0)
      q.push(i);

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int next_node : edges[node])
      if (--in_degrees[next_node] == 0) {
        q.push(next_node);
        levels[next_node] = levels[node] + 1;
      }
  }
}

void FindChildren(int node, vector<string>& children,
                  const vector<int>& decendents, const vector<int>& levels) {
  for (int child : decendents)
    if (levels[node] + 1 == levels[child])
      children.push_back(names[child]);
  sort(children.begin(), children.end());
}

void Solve() {
  unordered_map<string, int> name_to_index;
  vector<vector<int>> backward_edges(n);
  UnionFind union_find(n);

  for (int i = 0; i < n; ++i)
    name_to_index.insert({names[i], i});

  for (int i = 0; i < m; ++i) {
    int child = name_to_index[ancestors[i].first];
    int parent = name_to_index[ancestors[i].second];
    backward_edges[parent].push_back(child);
    union_find.Union(parent, child);
  }

  unordered_set<int> roots;
  for (int i = 0; i < n; ++i)
    roots.insert(union_find.Find(i));

  vector<string> root_names;
  for (int root : roots)
    root_names.push_back(names[root]);
  sort(root_names.begin(), root_names.end());

  cout << ssize(roots) << '\n';
  for (int i = 0; i < ssize(root_names); ++i)
    cout << root_names[i] << ' ';
  cout << '\n';

  vector<int> levels(n);
  TopologicalSort(backward_edges, levels);

  vector<vector<string>> childrens(n);
  for (int i = 0; i < n; ++i)
    FindChildren(i, childrens[i], backward_edges[i], levels);

  vector<pair<string, int>> names_with_index(n);
  for (int i = 0; i < n; ++i)
    names_with_index[i] = make_pair(names[i], i);
  sort(names_with_index.begin(), names_with_index.end());

  for (int i = 0; i < n; ++i) {
    string name = names_with_index[i].first;
    const vector<string>& children = childrens[names_with_index[i].second];
    cout << name << ' ' << ssize(children) << ' ';
    for (const string& child_name : children)
      cout << child_name << ' ';
    cout << '\n';
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
