#include <iostream>
using namespace std;

struct Query {
  char type;
  int i;
  union {
    int v;
    int j;
  };
};

int n, k;
int arr[100'001];
Query queries[100'001];
int segment_tree[400'000];

bool GetInput() {
  if (!(cin >> n >> k))
    return false;

  for (int i = 1; i <= n; ++i)
    cin >> arr[i];

  for (int i = 1; i <= k; ++i)
    cin >> queries[i].type >> queries[i].i >> queries[i].v;

  return true;
}

void Update(int index, int start, int end, int i, int new_value) {
  if (start == end) {
    if (new_value > 0)
      segment_tree[index] = 1;
    else if (new_value < 0)
      segment_tree[index] = -1;
    else
      segment_tree[index] = 0;

    return;
  }

  int mid = (start + end) / 2;
  if (i <= mid)
    Update(index * 2, start, mid, i, new_value);
  else
    Update(index * 2 + 1, mid + 1, end, i, new_value);

  int left = segment_tree[index * 2];
  int right = segment_tree[index * 2 + 1];
  segment_tree[index] = left * right;
}

int Multiply(int index, int start, int end, int query_from, int query_to) {
  if (query_to < start || end < query_from)
    return 1;

  if (query_from <= start && end <= query_to)
    return segment_tree[index];

  int mid = (start + end) / 2;
  int left = Multiply(index * 2, start, mid, query_from, query_to);
  int right = Multiply(index * 2 + 1, mid + 1, end, query_from, query_to);

  return left * right;
}

char GetSign(int val) {
  if (val > 0)
    return '+';
  else if (val < 0)
    return '-';
  else
    return '0';
}

void Solve() {
  for (int i = 1; i <= n; ++i)
    Update(1, 1, n, i, arr[i]);

  for (int i = 1; i <= k; ++i)
    if (queries[i].type == 'C')
      Update(1, 1, n, queries[i].i, queries[i].v);
    else
      cout << GetSign(Multiply(1, 1, n, queries[i].i, queries[i].j));

  cout << '\n';
}

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  while (GetInput())
    Solve();

  return 0;
}
