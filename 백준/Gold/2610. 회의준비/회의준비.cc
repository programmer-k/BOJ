#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class UnionFind {
 public:
  UnionFind(int size) : group_count_(size), parents_(size) {
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
    --group_count_;
    return true;
  }

  int GetGroupCount() {
    return group_count_;
  }

 private:
  int group_count_;
  vector<int> parents_;
};

int n, m;
vector<vector<int>> edges;
vector<pair<int, int>> relationships;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  edges.resize(n + 1);
  relationships.resize(m);
  for (int i = 0; i < m; ++i) {
    int node1, node2;
    cin >> node1 >> node2;

    edges[node1].push_back(node2);
    edges[node2].push_back(node1);

    relationships[i].first = node1;
    relationships[i].second = node2;
  }
}

int BreadthFirstSearch(int start_node) {
  queue<int> q;
  vector<int> visited(n + 1, -1);
  q.push(start_node);
  visited[start_node] = 0;

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int next_node : edges[node])
      if (visited[next_node] == -1) {
        q.push(next_node);
        visited[next_node] = visited[node] + 1;
      }
  }

  return *max_element(visited.begin(), visited.end());
}

void Solve() {
  UnionFind union_find(n + 1);

  for (const pair<int, int>& relationship : relationships)
    union_find.Union(relationship.first, relationship.second);

  vector<int> max_times(n + 1);
  for (int i = 1; i <= n; ++i)
    max_times[i] = BreadthFirstSearch(i);

  unordered_map<int, pair<int, int>> group_mins;
  int group_count = union_find.GetGroupCount() - 1;
  for (int i = 1; i <= n; ++i) {
    int group_num = union_find.Find(i);
    if (!group_mins.contains(group_num) ||
        max_times[i] < group_mins[group_num].first)
      group_mins[group_num] = {max_times[i], i};
  }

  vector<int> answers;
  for (const pair<const int, pair<int, int>>& group_min : group_mins)
    answers.push_back(group_min.second.second);
  sort(answers.begin(), answers.end());

  cout << group_count << '\n';
  for (int answer : answers)
    cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
