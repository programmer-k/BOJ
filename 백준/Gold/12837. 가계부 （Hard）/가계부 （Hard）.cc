#include <cstdint>
#include <iostream>
using namespace std;

struct Query {
  int type;
  int p;
  int q;
};

int n, q;
Query queries[100'000];
int64_t segment_tree[4'000'000];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> q;

  for (int i = 0; i < q; ++i)
    cin >> queries[i].type >> queries[i].p >> queries[i].q;
}

void Update(int index, int start, int end, int i, int add) {
  if (start == end) {
    segment_tree[index] += add;
    return;
  }

  int mid = (start + end) / 2;
  if (i <= mid)
    Update(index * 2, start, mid, i, add);
  else
    Update(index * 2 + 1, mid + 1, end, i, add);

  int64_t left = segment_tree[index * 2];
  int64_t right = segment_tree[index * 2 + 1];
  segment_tree[index] = left + right;
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

void Solve() {
  for (int i = 0; i < q; ++i)
    if (queries[i].type == 1)
      Update(1, 1, n, queries[i].p, queries[i].q);
    else
      cout << GetSum(1, 1, n, queries[i].p, queries[i].q) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
