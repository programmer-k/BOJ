#include <cstdint>
#include <iostream>
using namespace std;

const int kMaxSize = 100'000;

int n, q;
int arr[kMaxSize + 1];
int x[kMaxSize], y[kMaxSize], a[kMaxSize], b[kMaxSize];
int64_t segment_tree[kMaxSize * 4];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> q;

  for (int i = 1; i <= n; ++i)
    cin >> arr[i];

  for (int i = 0; i < q; ++i)
    cin >> x[i] >> y[i] >> a[i] >> b[i];
}

void Update(int index, int start, int end, int i, int new_val) {
  if (start == end) {
    segment_tree[index] = new_val;
    return;
  }

  int mid = (start + end) / 2;
  if (i <= mid)
    Update(index * 2, start, mid, i, new_val);
  else
    Update(index * 2 + 1, mid + 1, end, i, new_val);

  segment_tree[index] = segment_tree[index * 2] + segment_tree[index * 2 + 1];
}

int64_t GetSum(int index, int start, int end, int query_from, int query_to) {
  if (query_to < start || end < query_from)
    return 0;

  if (query_from <= start && end <= query_to)
    return segment_tree[index];

  int mid = (start + end) / 2;
  int64_t sum1 = GetSum(index * 2, start, mid, query_from, query_to);
  int64_t sum2 = GetSum(index * 2 + 1, mid + 1, end, query_from, query_to);

  return sum1 + sum2;
}

void Solve() {
  for (int i = 1; i <= n; ++i)
    Update(1, 1, n, i, arr[i]);

  for (int i = 0; i < q; ++i) {
    cout << GetSum(1, 1, n, min(x[i], y[i]), max(x[i], y[i])) << '\n';
    Update(1, 1, n, a[i], b[i]);
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
