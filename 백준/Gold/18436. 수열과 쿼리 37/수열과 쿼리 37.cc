#include <iostream>
using namespace std;

struct Query {
  int a;
  int b;
  int c;
};

int n, m;
int arr[100'001];
Query queries[100'000];
int segment_tree[400'000];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  for (int i = 1; i <= n; ++i)
    cin >> arr[i];

  cin >> m;

  for (int i = 0; i < m; ++i)
    cin >> queries[i].a >> queries[i].b >> queries[i].c;
}

void Update(int index, int start, int end, int i, int new_value) {
  if (start == end) {
    segment_tree[index] = new_value % 2 == 0 ? 0 : 1;
    return;
  }

  int mid = (start + end) / 2;
  if (i <= mid)
    Update(index * 2, start, mid, i, new_value);
  else
    Update(index * 2 + 1, mid + 1, end, i, new_value);

  int left = segment_tree[index * 2];
  int right = segment_tree[index * 2 + 1];
  segment_tree[index] = left + right;
}

int GetOddCount(int index, int start, int end, int query_from, int query_to) {
  if (query_to < start || end < query_from)
    return 0;

  if (query_from <= start && end <= query_to)
    return segment_tree[index];

  int mid = (start + end) / 2;
  int left = GetOddCount(index * 2, start, mid, query_from, query_to);
  int right = GetOddCount(index * 2 + 1, mid + 1, end, query_from, query_to);

  return left + right;
}

void Solve() {
  for (int i = 1; i <= n; ++i)
    Update(1, 1, n, i, arr[i]);

  for (int i = 0; i < m; ++i)
    if (queries[i].a == 1)
      Update(1, 1, n, queries[i].b, queries[i].c);
    else if (queries[i].a == 2)
      cout << queries[i].c - queries[i].b + 1 -
                  GetOddCount(1, 1, n, queries[i].b, queries[i].c)
           << '\n';
    else
      cout << GetOddCount(1, 1, n, queries[i].b, queries[i].c) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
