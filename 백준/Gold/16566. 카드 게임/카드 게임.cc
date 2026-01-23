#include <algorithm>
#include <iostream>
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
    x = Find(x);
    y = Find(y);

    parents_[x] = y;
  }

 private:
  vector<int> parents_;
};

int n, m, k;
int arr[4'000'000];
int queries[10'000];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> k;

  for (int i = 0; i < m; ++i)
    cin >> arr[i];

  for (int i = 0; i < k; ++i)
    cin >> queries[i];
}

void Solve() {
  UnionFind union_find(m + 1);
  sort(arr, arr + m);

  for (int i = 0; i < k; ++i) {
    int query = queries[i];
    int index = upper_bound(arr, arr + m, query) - arr;

    index = union_find.Find(index);
    union_find.Union(index, index + 1);

    cout << arr[index] << '\n';
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
