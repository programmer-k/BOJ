#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

struct Data {
  int a;
  int b;
  int64_t c;
};

int n, m, k;
vector<int64_t> arr, binary_indexed_tree;
vector<Data> operations;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> k;

  arr.resize(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> arr[i];

  operations.resize(m + k);
  for (int i = 0; i < m + k; ++i)
    cin >> operations[i].a >> operations[i].b >> operations[i].c;
}

int64_t GetSum(int i) {
  int64_t ret = 0;
  while (i > 0) {
    ret += binary_indexed_tree[i];
    i -= i & -i;
  }
  return ret;
}

void Update(int i, int64_t val) {
  while (i <= n) {
    binary_indexed_tree[i] += val;
    i += i & -i;
  }
}

void Solve() {
  binary_indexed_tree.resize(n + 1);
  for (int i = 1; i <= n; ++i)
    Update(i, arr[i]);

  for (const Data operation : operations)
    if (operation.a == 1) {
      Update(operation.b, operation.c - arr[operation.b]);
      arr[operation.b] = operation.c;
    } else
      cout << GetSum(operation.c) - GetSum(operation.b - 1) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
