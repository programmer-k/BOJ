#include <iostream>
#include <limits>
#include <utility>
#include <vector>
using namespace std;

int n, m;
vector<int> arr, segment_tree;
vector<pair<int, int>> queries;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  arr.resize(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> arr[i];

  queries.resize(m);
  for (int i = 0; i < m; ++i)
    cin >> queries[i].first >> queries[i].second;
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

  segment_tree[index] =
      min(segment_tree[index * 2], segment_tree[index * 2 + 1]);
}

int GetMin(int index, int start, int end, int query_left, int query_right) {
  if (query_right < start || end < query_left)
    return numeric_limits<int>::max();
  if (query_left <= start && end <= query_right)
    return segment_tree[index];

  int mid = (start + end) / 2;
  int val1 = GetMin(index * 2, start, mid, query_left, query_right);
  int val2 = GetMin(index * 2 + 1, mid + 1, end, query_left, query_right);
  return min(val1, val2);
}

void Solve() {
  segment_tree.resize(n * 4);
  for (int i = 1; i <= n; ++i)
    Update(1, 1, n, i, arr[i]);

  for (const pair<int, int>& query : queries)
    cout << GetMin(1, 1, n, query.first, query.second) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
