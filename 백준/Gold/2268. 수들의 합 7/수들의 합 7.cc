#include <cstdint>
#include <iostream>
using namespace std;

struct Function {
  int type;
  int i;
  union {
    int j;
    int k;
  };
};

int n, m;
Function functions[1'000'000];
int64_t segment_tree[4'000'000];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  for (int i = 0; i < m; ++i)
    cin >> functions[i].type >> functions[i].i >> functions[i].j;
}

int64_t GetSum(int index, int start, int end, int query_from, int query_to) {
  if (query_to < start || end < query_from)
    return 0;

  if (query_from <= start && end <= query_to)
    return segment_tree[index];

  int mid = (start + end) / 2;
  int64_t left = GetSum(index * 2, start, mid, query_from, query_to);
  int64_t right = GetSum(index * 2 + 1, mid + 1, end, query_from, query_to);

  return left + right;
}

void Update(int index, int start, int end, int i, int new_value) {
  if (start == end) {
    segment_tree[index] = new_value;
    return;
  }

  int mid = (start + end) / 2;
  if (i <= mid)
    Update(index * 2, start, mid, i, new_value);
  else
    Update(index * 2 + 1, mid + 1, end, i, new_value);

  int64_t left = segment_tree[index * 2];
  int64_t right = segment_tree[index * 2 + 1];
  segment_tree[index] = left + right;
}

void Solve() {
  for (int i = 0; i < m; ++i)
    if (functions[i].type == 0)
      cout << GetSum(1, 1, n, min(functions[i].i, functions[i].j), max(functions[i].i, functions[i].j)) << '\n';
    else
      Update(1, 1, n, functions[i].i, functions[i].k);
}

int main() {
  GetInput();
  Solve();
  return 0;
}
