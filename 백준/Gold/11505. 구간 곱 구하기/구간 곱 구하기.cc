#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

struct Operation {
  int a;
  int b;
  int c;
};

const int kMod = 1'000'000'007;

int n, m, k;
vector<int> arr;
vector<Operation> operations;
vector<int> segment_tree;

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

void Update(int index, int start, int end, int i, int new_value) {
  if (start == end) {
    segment_tree[index] = new_value;
    return;
  }

  int mid = (start + end) / 2;
  if (i <= mid) {
    Update(index * 2, start, mid, i, new_value);
  } else {
    Update(index * 2 + 1, mid + 1, end, i, new_value);
  }

  int64_t left = segment_tree[index * 2];
  int64_t right = segment_tree[index * 2 + 1];
  segment_tree[index] = left * right % kMod;
}

int Multiply(int index, int start, int end, int query_left, int query_right) {
  if (query_right < start || query_left > end)
    return 1;

  if (query_left <= start && end <= query_right)
    return segment_tree[index];

  int mid = (start + end) / 2;
  int64_t left = Multiply(index * 2, start, mid, query_left, query_right);
  int64_t right = Multiply(index * 2 + 1, mid + 1, end, query_left, query_right);
  return left * right % kMod;
}

void Solve() {
  segment_tree.resize(4 * n);
  for (int i = 1; i <= n; ++i)
    Update(1, 1, n, i, arr[i]);

  for (const Operation &operation : operations) {
    int a = operation.a;
    int b = operation.b;
    int c = operation.c;

    if (a == 1)
      Update(1, 1, n, b, c);
    else
      cout << Multiply(1, 1, n, b, c) << '\n';
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
