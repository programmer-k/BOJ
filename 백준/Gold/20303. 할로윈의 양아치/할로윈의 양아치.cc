#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class UnionFind {
 public:
  UnionFind(int size, const vector<int>& candies)
      : parents_(size), sizes_(size, 1), candies_(candies) {
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

    if (x > y)
      swap(x, y);

    parents_[y] = x;
    sizes_[x] += sizes_[y];
    candies_[x] += candies_[y];
    return true;
  }

  int GetSize(int index) {
    return sizes_[index];
  }

  int GetCandy(int index) {
    return candies_[index];
  }

 private:
  vector<int> parents_, sizes_, candies_;
};

int n, m, k;
vector<int> candies;
vector<vector<int>> edges;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> k;

  candies.resize(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> candies[i];

  edges.resize(n + 1);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    edges[a].push_back(b);
    edges[b].push_back(a);
  }
}

void Solve() {
  UnionFind union_find(n + 1, candies);
  for (int i = 1; i <= n; ++i)
    for (int next_node : edges[i])
      union_find.Union(i, next_node);

  vector<int> group_indices(1);
  for (int i = 1; i <= n; ++i)
    if (union_find.Find(i) == i)
      group_indices.push_back(i);

  int group_count = group_indices.size() - 1;
  vector<vector<int>> knapsack(group_count + 1, vector<int>(k));
  for (int i = 1; i <= group_count; ++i)
    for (int j = 0; j < k; ++j)
      knapsack[i][j] =
          max(knapsack[i - 1][j],
              j - union_find.GetSize(group_indices[i]) >= 0
                  ? knapsack[i - 1][j - union_find.GetSize(group_indices[i])] +
                        union_find.GetCandy(group_indices[i])
                  : 0);

  cout << knapsack[group_count][k - 1] << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
