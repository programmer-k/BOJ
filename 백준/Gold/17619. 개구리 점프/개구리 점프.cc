#include <algorithm>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

struct Data {
  int from;
  int to;
  int index;

  bool operator<(const Data& rhs) {
    return tie(from, to, index) < tie(rhs.from, rhs.to, rhs.index);
  }
};

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

int n, q;
vector<Data> arr;
vector<pair<int, int>> queries;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> q;

  int garbage;
  arr.resize(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> arr[i].from >> arr[i].to >> garbage;
    arr[i].index = i;
  }

  queries.resize(q + 1);
  for (int i = 1; i <= q; ++i)
    cin >> queries[i].first >> queries[i].second;
}

void Solve() {
  UnionFind union_find(n + 1);
  sort(arr.begin() + 1, arr.end());

  for (int i = 1, j = 2; i <= n && j <= n;) {
    if (arr[i].to >= arr[j].from) {
      union_find.Union(arr[i].index, arr[j].index);
      ++j;
    } else {
      ++i;
    }
  }

  for (int i = 1; i <= q; ++i)
    if (union_find.Find(queries[i].first) == union_find.Find(queries[i].second))
      cout << "1\n";
    else
      cout << "0\n";
}

int main() {
  GetInput();
  Solve();
  return 0;
}
