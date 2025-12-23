#include <iostream>
#include <limits>
#include <utility>
#include <vector>
using namespace std;

int n, m;
vector<int> arr;
vector<pair<int, int>> queries;
vector<int> max_segment_tree, min_segment_tree;

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

int GetMax(int index, int start, int end, int query_left, int query_right) {
  if (query_left > end || query_right < start)
    return 0;

  if (query_left <= start && end <= query_right)
    return max_segment_tree[index];

  int mid = (start + end) / 2;
  int candidate1 = GetMax(2 * index, start, mid, query_left, query_right);
  int candidate2 = GetMax(2 * index + 1, mid + 1, end, query_left, query_right);
  return max(candidate1, candidate2);
}

int GetMin(int index, int start, int end, int query_left, int query_right) {
  if (query_left > end || query_right < start)
    return numeric_limits<int>::max();

  if (query_left <= start && end <= query_right)
    return min_segment_tree[index];

  int mid = (start + end) / 2;
  int candidate1 = GetMin(2 * index, start, mid, query_left, query_right);
  int candidate2 = GetMin(2 * index + 1, mid + 1, end, query_left, query_right);
  return min(candidate1, candidate2);
}

void UpdateMax(int index, int start, int end, int i, int new_val) {
  if (start == end) {
    max_segment_tree[index] = new_val;
    return;
  }

  int mid = (start + end) / 2;
  if (i <= mid)
    UpdateMax(2 * index, start, mid, i, new_val);
  else
    UpdateMax(2 * index + 1, mid + 1, end, i, new_val);

  max_segment_tree[index] =
      max(max_segment_tree[2 * index], max_segment_tree[2 * index + 1]);
}

void UpdateMin(int index, int start, int end, int i, int new_val) {
  if (start == end) {
    min_segment_tree[index] = new_val;
    return;
  }

  int mid = (start + end) / 2;
  if (i <= mid)
    UpdateMin(2 * index, start, mid, i, new_val);
  else
    UpdateMin(2 * index + 1, mid + 1, end, i, new_val);

  min_segment_tree[index] =
      min(min_segment_tree[2 * index], min_segment_tree[2 * index + 1]);
}

void Solve() {
  max_segment_tree.resize(4 * n);
  min_segment_tree.resize(4 * n);

  for (int i = 1; i <= n; ++i) {
    UpdateMax(1, 1, n, i, arr[i]);
    UpdateMin(1, 1, n, i, arr[i]);
  }

  for (const pair<int, int>& query : queries) {
    int max_val = GetMax(1, 1, n, query.first, query.second);
    int min_val = GetMin(1, 1, n, query.first, query.second);
    cout << min_val << ' ' << max_val << '\n';
  }
}

int main() {
  GetInput();
  Solve();
  return 0;
}
