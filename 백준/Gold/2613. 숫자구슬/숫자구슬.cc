#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> arr;

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  arr.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
}

// Return whether the input can be grouped into `group` groups with maximum
// `maximum`.
bool CanCreateGroupWithMax(int group, int maximum) {
  int total = 0;
  int group_count = 1;
  for (int val : arr) {
    total += val;
    if (total > maximum) {
      total = val;
      ++group_count;
    }
  }

  if (group_count <= group)
    return true;
  return false;
}

void Solve() {
  int low = *max_element(arr.begin(), arr.end());
  int high = 30'000;
  while (low < high) {
    int mid = (low + high) / 2;

    if (CanCreateGroupWithMax(m, mid))
      high = mid;
    else
      low = mid + 1;
  }

  cout << low << '\n';

  int total = 0;
  vector<int> counts;
  int count = 0;
  for (int val : arr) {
    total += val;
    if (total > low) {
      total = val;
      counts.push_back(count);
      count = 0;
    }
    ++count;
  }
  counts.push_back(count);

  int zero_count = 0;
  counts.resize(m);
  for (int i = 0; i < m; ++i)
    if (counts[i] == 0) {
      counts[i] = 1;
      ++zero_count;
    }

  for (int i = m - 1; i >= 0; --i)
    if (counts[i] > 1) {
      int diff = counts[i] - 1;

      if (diff < zero_count) {
        zero_count -= diff;
        counts[i] = 1;
      } else {
        counts[i] -= zero_count;
        break;
      }
    }

  for (int val : counts)
    cout << val << ' ';
  cout << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
